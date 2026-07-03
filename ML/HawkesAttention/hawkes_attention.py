import torch
import torch.nn as nn
import math

class HawkesAttention(nn.Module):
    """
    Inputs:
      q:    (B, L, d_model) query embeddings (event embeddings projected)
      k:    (B, L, d_model) key embeddings
      v:    (B, L, d_model) value embeddings
      t_in: (B, L)          timestamps (scalar)
      c:    (B, L)          event type in [1..num_types]
    Output:
      out:  (B, L, d_model) Hidden representations h(t) for each token
    """
    def __init__(self, num_types, n_head, d_model, d_k, d_v,
                 phi_width, phi_depth, dropout=0.1, normalize_before=True):
        super().__init__()
        self.n_head = n_head
        self.d_model = d_model
        self.d_k = d_k
        self.d_v = d_v
        self.scale = math.sqrt(d_k) # or d_k**0.0.5
        self.normalize_before = normalize_before
        self.dropout = nn.Dropout(dropout)
        self.num_types = num_types
        self.phi_collector=None

        self.w_qs = nn.Linear(d_model, n_head * d_k, bias=False)
        self.w_ks = nn.Linear(d_model, n_head * d_k, bias=False)
        self.w_vs = nn.Linear(d_model, n_head * d_v, bias=False)
        nn.init.xavier_uniform_(self.w_qs.weight)
        nn.init.xavier_uniform_(self.w_ks.weight)
        nn.init.xavier_uniform_(self.w_vs.weight)

        self.fc = nn.Linear(n_head * d_v, d_model, bias=False)
        nn.init.xavier_uniform_(self.fc.weight)

        self.layer_norm = nn.LayerNorm(d_model, eps=1e-6)

        def build_phi():
            layers = []
            dim = 1 
            for _ in range(phi_depth):
                linear = nn.Linear(dim, phi_width)
                nn.init.xavier_uniform_(linear.weight) 
                layers = layers + [linear, nn.GELU(), nn.Dropout(dropout)]
                dim = phi_width

            final_linear = nn.Linear(dim, 1)
            nn.init.xavier_uniform_(final_linear.weight)
            layers.append(final_linear)

            return nn.Sequential(*layers)

        self.phi_dict = nn.ModuleDict({
            str(c): nn.ModuleList([build_phi() for _ in range(n_head)])
            for c in range(0, num_types)
        })

    def forward(self, q, k, v, t_in, c, mask=None):
        # print("HAWKES!!!")
        B, L, _ = q.size()
        H=self.n_head
        residual = q
        if self.normalize_before:
            q = self.layer_norm(q)

        qh = self.w_qs(q).view(B, L, H, self.d_k).transpose(1,2)  # (B,H,L,d_k)
        kh = self.w_ks(k).view(B, L, H, self.d_k).transpose(1,2)
        vh = self.w_vs(v).view(B, L, H, self.d_v).transpose(1,2)

        t_query = t_in.unsqueeze(2)
        t_key = t_in.unsqueeze(1)
        delta = t_query - t_key
        max_delta_t = delta.max().item()
        
        # build index tensor (B, L)
        c_index = c.long()
        
        # padding mask (B, L)
        padding_mask = (c == self.num_types)
        
        # index tensor for key and query
        c_i = c_index.unsqueeze(2).expand(-1, -1, L)  # (B, L, L) query
        c_j = c_index.unsqueeze(1).expand(-1, L, -1)  # (B, L, L) eky
        
        # exclude padding
        valid_mask = (~padding_mask.unsqueeze(2)) & (~padding_mask.unsqueeze(1))

        phiQ = torch.zeros(B, H, L, L, device=q.device)
        phiK = torch.zeros(B, H, L, L, device=q.device)
        
        for h in range(self.n_head):
            
            unique_types = torch.unique(c_index)
            unique_types = unique_types[unique_types != self.num_types]  # exclude padding type
            
            # only compute at the entries applicable to this type_val
            for type_val in unique_types:
                type_str = str(type_val.item())

                phi_net = self.phi_dict[type_str][h]

                type_mask_i = (c_i == type_val) & valid_mask
                type_mask_j = (c_j == type_val) & valid_mask
                
                if type_mask_i.any():
                    # get all delta t entries having type_val event as query and input to phi_type_val
                    delta_i = delta[type_mask_i].unsqueeze(-1)
                    phi_i = phi_net(delta_i).squeeze(-1)
                    
                    phiQ_h = torch.zeros(B, L, L, device=q.device)
                    phiQ_h[type_mask_i] = phi_i
                    phiQ[:, h] += phiQ_h
                
                if type_mask_j.any():
                    # similary to key
                    delta_j = delta[type_mask_j].unsqueeze(-1)
                    phi_j = phi_net(delta_j).squeeze(-1)

                    phiK_h = torch.zeros(B, L, L, device=q.device)
                    phiK_h[type_mask_j] = phi_j
                    phiK[:, h] += phiK_h

        # q_mod[i,j] = qh[...,j,:] * phiQ[...,i,j]
        q_mod = qh.unsqueeze(3) * phiQ.unsqueeze(-1)        # (B,H,L,L,d_k)
        k_mod = kh.unsqueeze(2) * phiK.unsqueeze(-1)        # (B,H,L,L,d_k)
        v_mod = vh.unsqueeze(2) * phiK.unsqueeze(-1)        # (B,H,L,L,d_v)

        scores = (q_mod * k_mod).sum(-1) / self.scale  # (B, H, L, L)

        if mask is not None:
            mask = mask.unsqueeze(1)
            scores = scores.masked_fill(mask, float('-inf'))
        #print(mask)

        attn = F.softmax(scores, dim=-1)
        #visualize_attention(attn, title="Attention Heatmap_masked")
        attn = self.dropout(attn)

        # print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
        out_heads = torch.einsum('b h i j, b h i j d -> b h i d', attn, v_mod)

        # merge and final projection, residual
        out = out_heads.transpose(1,2).contiguous().view(B, L, -1)  # (B,L,H*d_v)
        out = self.dropout(self.fc(out))                           # (B,L,d_model)
        out = out + residual
        if not self.normalize_before:
            out = self.layer_norm(out)



        if self.phi_collector is not None:

            delta_positive = delta[delta > 0].detach().cpu().numpy()
            t_positive = t_in[t_in > 0].detach().cpu().numpy()
            
            if 'delta_positive' not in self.phi_collector:
                self.phi_collector['delta_positive'] = delta_positive
            else:
                self.phi_collector['delta_positive'] = np.concatenate(
                    [self.phi_collector['delta_positive'], delta_positive]
                )

            if 't_positive' not in self.phi_collector:
                self.phi_collector['t_positive'] = t_positive
            else:
                self.phi_collector['t_positive'] = np.concatenate(
                    [self.phi_collector['t_positive'], t_positive]
                )

            for ty_str, phi_nets in self.phi_dict.items():
                ty = int(ty_str)
                for h in range(H):
                    if (ty, h) not in self.phi_collector:
                        self.phi_collector[(ty, h)] = {'phi_net': phi_nets[h], 'max_delta_t': max_delta_t}
                    else:
                        self.phi_collector[(ty, h)]['max_delta_t'] = max(self.phi_collector[(ty, h)]['max_delta_t'], max_delta_t)


        return out