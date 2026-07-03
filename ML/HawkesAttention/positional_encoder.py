import torch
import torch.nn as nn


class Encoder(nn.Module):
    def __init__(
        self,
        embed_dim: int,
        event_dim: int,
        time_base: float = 1000.0,
    ):
        super().__init__()

        self.embed_dim = embed_dim
        self.event_dim = event_dim
        self.time_base = time_base

        self.event_embedding = nn.Embedding(
            num_embeddings=event_dim,
            embedding_dim=embed_dim,
        )

    def forward(self, event_times: torch.Tensor, event_types: torch.Tensor):
        time_encoding = self.time_encoding(event_times=event_times)
        type_encoding = self.event_type_encoding(event_types=event_types)
        return type_encoding + time_encoding

    def time_encoding(self, event_times: torch.Tensor) -> torch.Tensor:
        event_times = event_times.to(dtype=self.event_embedding.weight.dtype)

        dim = torch.arange(
            1,
            self.embed_dim + 1,
            device=event_times.device,
            dtype=event_times.dtype,
        )
        exponent = torch.where(
            condition=dim.remainder(2) == 1,
            input=(dim - 1) / self.embed_dim,
            other=dim / self.embed_dim,
        )
        angles = event_times.unsqueeze(-1) / (self.time_base ** exponent)

        encoding = torch.empty_like(angles)
        encoding[..., 0::2] = torch.cos(angles[..., 0::2])
        encoding[..., 1::2] = torch.sin(angles[..., 1::2])
        return encoding

    def event_type_encoding(
        self,
        event_types: torch.Tensor,
    ) -> torch.Tensor:
        return event_types.to(dtype=self.event_embedding.weight.dtype) @ self.event_embedding.weight
