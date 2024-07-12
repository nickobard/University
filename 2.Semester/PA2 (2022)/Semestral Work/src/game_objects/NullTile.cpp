#include "NullTile.hpp"

NullTile::NullTile(const Vector2<float> &position)
        : Tile(nullptr, position) {}

void NullTile::Render() const {
}

TileType NullTile::GetType() const {
    return TileType::NONE;
}

bool NullTile::isObstacle() const {
    return true;
}
