import torch
import torch.nn as nn
import torch.nn.functional as F
from collections import OrderedDict
import math


class MLP(nn.Module):
    def __init__(self, input_dim: int, mlp_depth: int, output_dim: int):
        super().__init__()

        self.network = nn.Sequential(OrderedDict({
            'lin_1': nn.Linear(in_features=input_dim, out_features=mlp_depth),
            'act_1': nn.GELU(),
            'lin_2': nn.Linear(in_features=mlp_depth, out_features=output_dim),
        }))
    def forward(self, x):
        return self.network(x)
    
class Attention(nn.Module):
    def __init__(self, embed_dim: int, key_dim: int, value_dim: int):
        super().__init__()

        self.W_q = nn.Linear(in_features=embed_dim, out_features=key_dim, bias=False)
        self.W_k = nn.Linear(in_features=embed_dim, out_features=key_dim, bias=False)
        self.W_v = nn.Linear(in_features=embed_dim, out_features=value_dim, bias=False)

        self.key_dim = key_dim
    
    def forward(self, x):
        # x: [batch_size, num_tokens, embed_dim]
        # or: [num_tokens, embed_dim]

        Q = self.W_q(x)  # [..., num_tokens, key_dim]
        K = self.W_k(x)  # [..., num_tokens, key_dim]
        V = self.W_v(x)  # [..., num_tokens, embed_dim]

        scores = Q @ K.transpose(-2, -1)
        # scores: [..., num_tokens, num_tokens]

        scores = scores / math.sqrt(self.key_dim)

        attention_weights = F.softmax(scores, dim=-1)
        # softmax over "which key/token should this query attend to?"

        out = attention_weights @ V
        # out: [..., num_tokens, embed_dim]
        # matmul on tensors of dimension >= 2 batches on the last 2-dimensions to do the regular matrix multiplication there.

        return out
    
class CausalAttention(Attention):
    def __init__(self, embed_dim: int, key_dim: int, value_dim: int):
        super().__init__(embed_dim=embed_dim, key_dim=key_dim, value_dim=value_dim)
        
    def forward(self, x):
        Q = self.W_q(x)
        K = self.W_k(x)
        V = self.W_v(x)

        scores = Q @ K.transpose(-2, -1)
        scores = scores / math.sqrt(self.key_dim)
        scores = scores.masked_fill(torch.triu(torch.ones_like(scores, device=scores.device, dtype=torch.bool), diagonal=1,), float("-inf"))

        attention_weights = F.softmax(input=scores, dim=-1)
        
        out = attention_weights @ V
        
        return out
        
class MultiHeadAttention(nn.Module):
    def __init__(self, embed_dim: int, keys_dim: list[int], value_dim: int, causal = False):
        super().__init__()
        n_heads = len(keys_dim)

        if causal:
            self.heads = nn.ModuleList([
            CausalAttention(
                embed_dim=embed_dim,
                key_dim=keys_dim[h],
                value_dim=value_dim,
            )
            for h in range(n_heads)
        ])
        else:
            self.heads = nn.ModuleList([
            Attention(
                embed_dim=embed_dim,
                key_dim=keys_dim[h],
                value_dim=value_dim,
            )
            for h in range(n_heads)
        ])
        
        self.aggregator = nn.Linear(
            in_features=n_heads * value_dim,
            out_features=embed_dim,
            bias=False,
            )
        
        self.keys_dim = keys_dim

    def forward(self, x):
        # x: [B, N, embed_dim]

        head_outputs = [head(x) for head in self.heads]
        # each: [B, N, value_dim]

        combined = torch.cat(head_outputs, dim=-1)
        # [B, N, n_heads * value_dim]

        return self.aggregator(combined)
        # [B, N, embed_dim]