#pragma once

#include "GameStateReset.hpp"

/**
 * @brief Represents game over state of the game, when player wins.
 */
class GameStateOver : public GameStateReset {

public:

    void Update() override;

    void FixedUpdate() override;

    void InitGameState() override;

private:

    /// Delay before next state or event occurs.
    static constexpr float GAME_OVER_DELAY = 4.0f;

};