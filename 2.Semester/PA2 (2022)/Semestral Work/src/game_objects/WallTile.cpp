#include "WallTile.hpp"

WallTile::WallTile(Texture *texture, const Vector2<float> &position)
        : Tile(texture, position) {}

TileType WallTile::GetType() const {
    return TileType::WALL;
}

bool WallTile::isObstacle() const {
    return true;
}