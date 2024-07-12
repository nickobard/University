#include "SDL2/SDL.h"

class GameEvents {
  public:
    // Constructs the game events object.
    GameEvents();
    // Handles input if game should quit or not.
    void ProcessInput();
    // Sets game to quit on the next frame, not immideately.
    void QuitGame();
    // Checks whether game should stop and quit or not.
    inline bool isQuit () const;
    // @return true - pops event queue - if that 
    // that one was last. False - if there are still
    // some pending events to process.
    inline bool hasEmptiedEventQueue();
    // @return true if current event is quit event,
    // giving signal to close the game 
    inline bool isQuitEvent() const;
  private:
    // Quit flag - whether game should end and quit.
    bool quit_;
    // Event handler to handle events on the event queue.
    SDL_Event event_;
};

inline
bool GameEvents::isQuit() const {
  return quit_;
}

inline 
bool GameEvents::hasEmptiedEventQueue(){
  return SDL_PollEvent ( &event_ ) == 0;
}

inline
bool GameEvents::isQuitEvent() const {
  return event_.type == SDL_QUIT;
}