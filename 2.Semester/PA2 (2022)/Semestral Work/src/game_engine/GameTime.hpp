#pragma once

#include <SDL2/SDL.h>

using namespace std;

/**
 * @brief Game Time class which handles time across all the game.
 */
class GameTime {

public:

    /**
     * @brief Constructs game time object.
     */
    GameTime();

    /**
     * @brief Initialized game timer with 0 ticks,
     * and last ticks with time since game start.
     */
    void InitGameTicks();

    /**
     * @brief Update current ticks with actual SDL time in ticks
     * and calculate delta ticks between current and last ticks.
     */
    void UpdateCurrentTicks();

    /**
     * @brief Update last ticks with current ticks
     * Sets to the value from the start of the current game loop frame.
     */
    void UpdateLastTicks();

    /// Get the delta ticks in milliseconds.
    inline uint GetDeltaTicks() const;

    /// Get the delta ticks in seconds.
    inline float GetDeltaTime() const;

private:

    /// Current ticks at the end of the frame.
    uint64_t currentTicks_;
    /// Previous ticks at the start of the frame
    uint64_t lastTicks_;
    /// Difference between current ticks and previous ticks - frame delta time.
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