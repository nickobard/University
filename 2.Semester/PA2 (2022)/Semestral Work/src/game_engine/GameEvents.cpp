#include "GameEvents.hpp"

GameEvents::GameEvents()
: quit_ (false)
{}

void GameEvents::ProcessInput() {
  //Handle events on queue
  while ( !hasEmptiedEventQueue()){
    //User requests quit
    if ( isQuitEvent())
      QuitGame();
  }
}

void GameEvents::QuitGame() {
  quit_ = true;
}