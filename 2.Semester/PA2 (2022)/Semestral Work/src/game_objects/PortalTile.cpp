#include "PortalTile.hpp"
#include "../structures/TileNode.hpp"
#include "../game_engine/GameLocator.hpp"

PortalTile::PortalTile(Texture *texture, const Vector2<float> &position, const Vector2<float> &direction)
        : TunnelTile(texture, position) {
    transform_->direction_ = direction;
}

TileType PortalTile::GetType() const {
    return TileType::PORTAL;
}

bool PortalTile::isPortal() const {
    return true;
}

void PortalTile::Teleport(GameActor &gameActor, TileNode &portal) {

    auto exit = portal.NextNode(-transform_->direction_);
    auto exitDirection = exit->GetTransform()->direction_;
    auto exitPosition = exit->GetTransform()->position_;

    gameActor.GetPhysics()->currentNode_ = exit;
    gameActor.GetTransform()->position_ = exitPosition + exitDirection * TILE_SIZE / 2;
    gameActor.GetTransform()->direction_ = exitDirection;
}
