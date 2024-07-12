#include "TunnelTile.hpp"

TunnelTile::TunnelTile(Texture *texture, const Vector2<float> &position)
        : EmptyTile(texture, position) {}

TileType TunnelTile::GetType() const {
    return TileType::TUNNEL;
}

bool TunnelTile::isTunnel() const {
    return true;
}

