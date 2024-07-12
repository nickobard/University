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

}

void GameStateOver::FixedUpdate() {
    if (delay_ > 0.0f)
        delay_ -= GameTime::FMS_PER_UPDATE;
    else
        manager_->game_.QuitGame();
}

