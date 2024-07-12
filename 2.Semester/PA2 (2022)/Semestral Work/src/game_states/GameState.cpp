#include "GameState.hpp"

GameManager *GameState::manager_;

void GameState::ProvideGameManager(GameManager &manager) {
    manager_ = &manager;
}
