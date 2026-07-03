from architectures import MultiHeadAttention, MLP
from positional_encoder import Encoder
import torch.nn as nn
import torch

class IntensityNetwork(nn.Module):
    def __init__(self, state_dim: int, event_dim: int, beta: float):
        super().__init__()
        self.state_layer = nn.Linear(in_features=state_dim, out_features=event_dim)
        self.time_factor = nn.Linear(in_features=1, out_features=event_dim)
        self.softplus = nn.Softplus(beta=beta)
    def forward(self, t, curr_time, state_factor):
        return self.softplus(self.time_factor(((t-curr_time) / curr_time).unsqueeze(-1)) + self.state_layer(state_factor))

class TransformerHawkesProcess(nn.Module):
    def __init__(self, embed_dim: int, event_dim: int, key_dim: int, value_dim: int, mlp_depth: int, state_dim: int, n_heads: int = 1, time_base = 10000.0, beta=1.0):
        super().__init__()
        self.encoder: nn.Module = Encoder(embed_dim=embed_dim, event_dim=event_dim, time_base=time_base)
        self.attention = MultiHeadAttention(embed_dim=embed_dim, keys_dim=[key_dim for _ in range(n_heads)], value_dim=value_dim, causal=True)
        self.state_mlp = MLP(input_dim=embed_dim, mlp_depth=mlp_depth, output_dim=state_dim)
        self.intensity_network = IntensityNetwork(state_dim=state_dim, event_dim=event_dim, beta=beta)
        
    def forward(self, times, event_times, event_types):
        X: torch.Tensor = self.encoder(event_times=event_times, event_types=event_types)
        S: torch.Tensor = self.attention(X)
        H: torch.Tensor = self.state_mlp(S)
        intensities = self.intensity_network(times[:,1:], times[:,:-1], H[:,:-1])
        return intensities