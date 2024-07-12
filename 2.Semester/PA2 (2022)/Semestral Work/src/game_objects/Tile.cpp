#include "Tile.hpp"

Tile::Tile(Texture *texture, const Vector2<float> &position)
        : graphics_(new GraphicsComponent(texture))
          , transform_(new TransformComponent(position)) {}

Tile::Tile(Texture *texture, TransformComponent *transform)
        : graphics_(new GraphicsComponent(texture))
          , transform_(transform) {}

Tile::~Tile() {
    delete graphics_;
    delete transform_;
}

Vector2<float> Tile::GetOffsetFromTileCenter(const GameActor &gameActor, const Tile *tile) {
    return (gameActor.GetTransform()->position_ - tile->GetTransform()->position_) *
           gameActor.GetTransform()->direction_;

}

void Tile::Update() {

}

void Tile::Render() const {
    graphics_->Render(transform_->position_);
}

bool Tile::isObstacle() const {
    return false;
}

bool Tile::isTunnel() const {
    return false;
}

bool Tile::isPortal() const {
    return false;
}

void Tile::Teleport(GameActor &gameActor, TileNode &portalNode) {

}

bool Tile::CanTurnAside(const GameActor &gameActor) const {
    return false;
}

bool Tile::AddBonus(Bonus *bonus) {
    return false;
}

bool Tile::CollectBonus() {
    return false;
}

void Tile::FixedUpdate() {

}

