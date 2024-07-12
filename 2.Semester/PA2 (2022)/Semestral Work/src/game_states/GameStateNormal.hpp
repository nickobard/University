#pragma once

#include "GameState.hpp"

/**
 * @brief Represents normal state of the game.
 */
class GameStateNormal : public GameState {

public:

    /**
     * @brief Constructs normal game state object.
     */
    GameStateNormal();

    void Update() override;

    void PlayerCollision() override;

    void InitGameState() override;

    /**
     * @brief Set total amount of bonuses in the game.
     * @param amount of bonuses to be set.
     */
    static void SetBonusAmount(int amount);

    /**
     * @brief Decrement amount of bonuses by one.
     */
    static void DecrementBonus();

private:

    /**
     * @brief Disable all controllers.
     */
    void DisableControllers();

    /// Current player lives.
    int playerLives_;

    /// Represents current bonuses.
    static int bonuses_;

    /// Initial player lives for each game.
    static constexpr int MAX_PLAYER_LIVES = 3;

};