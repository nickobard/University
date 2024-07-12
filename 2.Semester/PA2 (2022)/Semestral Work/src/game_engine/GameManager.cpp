#include "GameManager.hpp"
#include "GameLocator.hpp"
#include "Game.hpp"

GameManager::GameManager(Game &game)
        : game_(game) {
    GameState::ProvideGameManager(*this);
    state_ = &GameState::normal_;
}

void GameManager::Update() {
    state_->Update();
}

void GameManager::ReportPlayerCollision() {
    state_->PlayerCollision();
}

void GameManager::ReportBonusCollection() {
    GameStateNormal::DecrementBonus();
}

void GameManager::FixedUpdate() {
    state_->FixedUpdate();
}
