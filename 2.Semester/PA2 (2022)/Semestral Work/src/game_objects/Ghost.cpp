#include "Ghost.hpp"
#include "../game_engine/GameLocator.hpp"

Ghost::Ghost(TransformComponent *transform, GraphicsComponent *graphics)
        : GameActor(transform, graphics, *this) {
    state_ = MOVING;
    physics_->currentNode_ = GameLocator::GetMap().GetMapInfo().ghostsSpawn_;
}

void Ghost::TurnUp() {
    TurnTo(Vector2<float>::Up());
}

void Ghost::TurnDown() {
    TurnTo(Vector2<float>::Down());
}

void Ghost::TurnRight() {
    TurnTo(Vector2<float>::Right());
}

void Ghost::TurnLeft() {
    TurnTo(Vector2<float>::Left());
}

void Ghost::StopMoving() {
    state_ = MOVING;
}

void Ghost::Update() {

}

void Ghost::Render() const {
    graphics_->Render(transform_->position_);

}

void Ghost::TurnTo(const Vector2<float> &newDirection) {
    if (state_ == STANDING)
        state_ = MOVING;
    transform_->direction_ = newDirection;
    transform_->position_ = physics_->currentNode_->GetTransform()->position_;
}

void Ghost::Move() {
    auto newPosition =
            transform_->position_ + transform_->direction_ * (GameTime::FMS_PER_UPDATE * velocity_);
    physics_->Move(newPosition);
}

void Ghost::FixedUpdate() {
    CheckTunnel();
}

void Ghost::CheckTunnel() {
    if (physics_->currentNode_->isTunnel())
        velocity_ = 100.0f;
    else
        velocity_ = GameManager::GAME_SPEED;
}
