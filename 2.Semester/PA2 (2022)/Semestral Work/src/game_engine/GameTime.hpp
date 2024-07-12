#pragma once
#include <SDL2/SDL.h>
using namespace std;
/**
 * @brief Game Time class which handles time across all the game.
 * 
 */
class GameTime {
  public:
    GameTime();
    // Initialized game timer with 0, 
    // and last ticks with time since game start.
    void InitGameTicks();
    // Update current ticks with actual time 
    // and calculate deltaTime
    void UpdateCurrentTicks();
    /**
     * @brief Update the lastTicks member at the end of the gameLoop()
     * 
     * Sets to the value from the start of the current game loop frame
     * 
     */
    void UpdateLastTicks();
    /**
     * @brief Get the Delta Ticks object - integer value in miliseconds
     * 
     * @return uint - number of miliseconds between frames
     */
    inline uint GetDeltaTicks() const ;
    /**
     * @brief Get the Delta Time object - float value in seconds
     * 
     * @return float - time in seconds between frames
     */
    inline float GetDeltaTime() const ;
  private:
    // current ticks at the end of the frame
    uint64_t currentTicks_;
    // previuos ticks at the start of the frame
    uint64_t lastTicks_;
    // difference between frames
    uint deltaTicks_;
};



inline 
uint GameTime::GetDeltaTicks() const {
  return deltaTicks_;
}

inline 
float GameTime::GetDeltaTime() const {
  return static_cast<float>(deltaTicks_) / 1000;
}