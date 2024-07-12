#include "GameStateNormal.hpp"
#include "GameStateOver.hpp"
#include "../game_engine/GameLocator.hpp"
#include "../game_engine/Game.hpp"

GameStateNormal GameState::normal_;
int GameStateNormal::bonuses_;

GameStateNormal::GameStateNormal()
        : playerLives_(MAX_PLAYER_LIVES) {}

void GameStateNormal::Update() {
    if (playerLives_ < 1)
        manager_->game_.QuitGame();
    else if (bonuses_ < 1) {
        DisableControllers();
        manager_->state_ = &GameState::over_;
        manager_->state_->InitGameState();
    }

}

void GameStateNormal::PlayerCollision() {
    DisableControllers();
    playerLives_--;
    manager_->state_ = &GameState::reset_;
    manager_->state_->InitGameState();
}

void GameStateNormal::DisableControllers() {
    auto &controllers = manager_->game_.gameControllers_;
    for (auto controller: controllers)
        controller->SetState(Controller::DISABLED);
}

void GameStateNormal::DecrementBonus() {
    bonuses_--;
}

void GameStateNormal::SetBonusAmount(int amount) {
    bonuses_ = amount;
}

void GameStateNormal::InitGameState() {

}
