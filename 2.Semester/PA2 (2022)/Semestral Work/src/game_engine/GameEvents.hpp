#include "SDL2/SDL.h"

/**
 * @brief Low level class that handles SDL events.
 */
class GameEvents {

public:

    /**
     * @brief Constructs the game events object.
     */
    GameEvents();

    /**
     * @brief Handles input if game should quit or not.
     */
    void ProcessInput();

    /**
     * @brief Sets game to quit on the next frame, not immediately.
     */
    void QuitGame();

    /**
     * @brief Checks whether game should stop and quit or not.
     * @return true if is quit event.
     * @return false if is NOT quit event.
     */
    inline bool isQuit() const;

    /**
     * @return ture if current event is quit event.
     * @return false if current event is NOT quit event.
     */
    inline bool isQuitEvent() const;

private:

    /// Quit flag - whether game should end and quit.
    bool quit_;
    /// Event handler to handle events on the event queue.
    SDL_Event event_;
};

inline
bool GameEvents::isQuit() const {
    return quit_;
}

inline
bool GameEvents::isQuitEvent() const {
    return event_.type == SDL_QUIT;
}