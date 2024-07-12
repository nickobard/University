#include "GameEvents.hpp"

GameEvents::GameEvents()
        : quit_(false) {}

void GameEvents::ProcessInput() {
    bool notEmptyEventQueue = true;
    //Handle events on queue
    while (notEmptyEventQueue) {
        notEmptyEventQueue = SDL_PollEvent(&event_);
        //User requests quit
        if (isQuitEvent())
            QuitGame();
    }
}

void GameEvents::QuitGame() {
    quit_ = true;
}