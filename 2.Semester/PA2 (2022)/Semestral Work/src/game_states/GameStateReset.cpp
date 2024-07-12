#include "GameStateReset.hpp"
#include "../game_engine/GameLocator.hpp"
#include "../game_engine/Game.hpp"

GameStateReset GameState::reset_;

GameStateReset::GameStateReset()
        : delay_(0.0f) {}

void GameStateReset::Update() {

}

void GameStateReset::PlayerCollision() {
}

void GameStateReset::ResetControllers() {
    auto &controllers = manager_->game_.gameControllers_;
    for (auto controller: controllers) {
        controller->GetController()->ResetControlled();
        controller->SetState(Controller::ENABLED);
    }
}

void GameStateReset::InitGameState() {
    delay_ = RESET_DELAY;
}

void GameStateReset::FixedUpdate() {
    if (delay_ > 0.0f)
        delay_ -= GameTime::FMS_PER_UPDATE;
    else {
        ResetControllers();
        manager_->state_ = &GameState::normal_;
    }
}

