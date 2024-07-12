#include "GameLocator.hpp"

GameTime        * GameLocator::time_      ;
GameMap         * GameLocator::map_       ;
GameFilesystem  * GameLocator::filesystem_;
GameAudio       * GameLocator::audio_     ;
GameGraphics    * GameLocator::graphics_  ;
GameManager     * GameLocator::manager_   ;

void GameLocator::InitLocator () {
  time_       = nullptr;
  map_        = nullptr;
  filesystem_ = nullptr;
  audio_      = nullptr;
  manager_    = nullptr;
  graphics_   = nullptr;
}

void GameLocator::QuitLocator() {
  delete time_      ;
  delete graphics_  ;
  delete map_       ;
  delete filesystem_;
  delete manager_   ;
  delete audio_     ;
}
