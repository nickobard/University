#include "Pacman.hpp"
#include "../game_engine/GameLocator.hpp"

Pacman::Pacman(TransformComponent *transform, GraphicsComponent *graphics)
        : GameActor(transform, graphics, *this) {
    physics_->currentNode_ = GameLocator::GetMap().GetMapInfo().playerSpawn_;
}

void Pacman::TurnUp() {
    TryChangeDirection(Vector2<float>::Up());
}

void Pacman::TurnDown() {
    TryChangeDirection(Vector2<float>::Down());
}

void Pacman::TurnRight() {
    TryChangeDirection(Vector2<float>::Right());
}

void Pacman::TurnLeft() {
    TryChangeDirection(Vector2<float>::Left());
}

void Pacman::StopMoving() {
    state_ = STANDING;
}

void Pacman::Update() {
}

void Pacman::Render() const {
    graphics_->Render(transform_->position_, transform_->direction_.ToDegrees());
}

void Pacman::TurnTo(const Vector2<float> &direction) {
    TryChangeDirection(direction);
}

void Pacman::TryChangeDirection(const Vector2<float> &newDirection) {

    if (state_ == STANDING)
        state_ = MOVING;

    if (newDirection == transform_->direction_)
        return;
    else if (newDirection == transform_->direction_.ToBack())
        transform_->direction_ = newDirection;
    else if (physics_->currentNode_->CanTurnAside(*this) && !physics_->TouchesObstacle(newDirection))
        transform_->direction_ = newDirection;
}

void Pacman::Move() {
    if (state_ == MOVING) {
        auto newPosition =
                transform_->position_ + transform_->direction_ * (GameTime::FMS_PER_UPDATE * velocity_);
        physics_->Move(newPosition);
    }
}

void Pacman::CollectBonus() {
    physics_->currentNode_->CollectBonus();
}

void Pacman::FixedUpdate() {
    CollectBonus();
}
