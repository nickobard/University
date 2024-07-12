#include "GameTime.hpp"

GameTime::GameTime ()
: currentTicks_ (SDL_GetTicks64())
, lastTicks_ (0)
, deltaTicks_ (0)
{}

void GameTime::InitGameTicks() {
  lastTicks_ = SDL_GetTicks64();
}

void GameTime::UpdateCurrentTicks() {
  currentTicks_ = SDL_GetTicks64();
  deltaTicks_ = currentTicks_ - lastTicks_;
}

void GameTime::UpdateLastTicks() {
  lastTicks_ = currentTicks_;
}

