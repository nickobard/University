#include "EmptyTile.hpp"

EmptyTile::EmptyTile(Texture *texture, const Vector2<float> &position)
        : Tile(texture, position)
          , bonus_(nullptr) {}

EmptyTile::~EmptyTile() {
    delete bonus_;
}

void EmptyTile::Render() const {
    graphics_->Render(transform_->position_);
    if (bonus_ != nullptr)
        bonus_->Render(transform_->position_);
}

TileType EmptyTile::GetType() const {
    return TileType::EMPTY;
}

bool EmptyTile::CanTurnAside(const GameActor &gameActor) const {
    return false;
}

bool EmptyTile::AddBonus(Bonus *bonus) {
    delete bonus_;
    bonus_ = bonus;
    return true;
}

bool EmptyTile::CollectBonus() {
    delete bonus_;
    bonus_ = nullptr;
    return true;
}