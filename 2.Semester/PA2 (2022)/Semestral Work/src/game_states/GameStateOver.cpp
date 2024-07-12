#include <iostream>

#include "../game_engine/Game.hpp"
#include "../game_engine/GameLocator.hpp"
#include "GameStateOver.hpp"

using namespace std;

GameStateOver GameState::over_;

void GameStateOver::InitGameState() {
    cout << "You win! Game is over!" << endl;
    delay_ = GAME_OVER_DELAY;
}

void GameStateOver::Update() {
    if (delay_ > 0.0f)
        delay_ -= GameLocator::GetTime().GetDeltaTime();
    else
        manager_->game_.QuitGame();
}

