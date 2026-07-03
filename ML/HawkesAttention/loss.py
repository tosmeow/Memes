import torch
import torch.nn as nn

class LogLikelihoodPP(nn.Module):
    def __init__(self, eps=1e-8):
        super().__init__()
        self.eps = eps

    def forward(self, times, intensities, event_types):
        # intensities: [B, L-1, K], evaluated at t_{j+1} using h(t_j)
        # event_types: [B, L, K]

        dt = torch.diff(times, dim=1)  # [B, L-1]
        target_types = event_types[:, 1:]  # [B, L-1, K]

        event_ll = (target_types * torch.log(intensities + self.eps)).sum(dim=-1)
        non_event_ll = dt * intensities.sum(dim=-1)

        log_likelihood = event_ll - non_event_ll
        return -log_likelihood.sum()