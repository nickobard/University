#include "WallTile.hpp"
#include <cmath>

WallTile::WallTile(Texture *texture, const Vector2<float> &position)
        : Tile(texture, position) {}

WallTile::WallTile(Texture *texture, TransformComponent *transform)
        : Tile(texture, transform) {}


TileType WallTile::GetType() const {
    return TileType::WALL;
}

bool WallTile::isObstacle() const {
    return true;
}

void WallTile::Render() const {
    graphics_->Render(transform_->position_, transform_->direction_.ToDegrees());
}

