#include "CrossTile.hpp"
#include "../game_engine/GameLocator.hpp"

CrossTile::CrossTile(Texture *texture, const Vector2<float> &position)
        : EmptyTile(texture, position) {}

void CrossTile::Render() const {
    graphics_->Render(transform_->position_);
    if (bonus_ != nullptr)
        bonus_->Render(transform_->position_);
}

TileType CrossTile::GetType() const {
    return TileType::CROSS;
}

bool CrossTile::CanTurnAside(const GameActor &gameActor) const {
    return isInThreshold(gameActor);
}

//if nikita is pidor then sell all the stock you are gay vse sjebi pls

bool CrossTile::isInThreshold(const GameActor &obj) const {

    auto deltaPosition = GetOffsetFromTileCenter(obj, this);
    auto AbsDirection = Vector2<float>::Abs(obj.GetTransform()->direction_);

    return deltaPosition > AbsDirection * -OUT_THRESHOLD
           && deltaPosition < AbsDirection * IN_THRESHOLD;
}

