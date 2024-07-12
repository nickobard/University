#pragma once

#include "../game_states/GameState.hpp"
#include "../game_states/GameStateNormal.hpp"
#include "../game_states/GameStateReset.hpp"

class Game;

/**
 * @brief Class which manages game, what happens there and affect game objects.
 */
class GameManager {

public:

    /**
     * @brief Constructs game manager object.
     * @param game which is managed by game manager.
     */
    explicit GameManager(Game &game);

    /**
     * @brief Checks game state each frame.
     */
    void Update();

    /**
     * @brief Reports that player was collided with ghost.
     */
    void ReportPlayerCollision();

    /**
     * @brief Reports bonus collection to current state.
     */
    static void ReportBonusCollection();

    /// Represents default game speed.
    static constexpr float GAME_SPEED = 200.0f;

    /// Represents current game state.
    GameState *state_;

    /// Currently running game.
    Game &game_;

};
