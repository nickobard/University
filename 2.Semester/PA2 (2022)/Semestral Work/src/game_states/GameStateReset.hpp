#pragma once

#include "GameState.hpp"

/**
 * @brief Class that represents game state on reset after collision.
 */
class GameStateReset : public GameState {

public:

    /**
     * @brief Constructs reset game state.
     */
    GameStateReset();

    void Update() override;

    void FixedUpdate () override;

    void PlayerCollision() override;

    void InitGameState() override;

protected:

    /// Delay before reset to give player some time to consider about what happened, about his life and other things.
    float delay_;

private:

    /**
     * @brief Resets all controllers and their actors ot initial positions.
     */
    static void ResetControllers();

    /// How long in seconds should delay last.
    static constexpr float RESET_DELAY = 3.0f;

};