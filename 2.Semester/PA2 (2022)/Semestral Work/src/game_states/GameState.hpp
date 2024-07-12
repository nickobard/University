#pragma once

class GameManager;

class GameStateOver;

class GameStateNormal;

class GameStateReset;

/**
 * @brief Class that represents game state.
 */
class GameState {

public:


    /**
     * @brief Destructs game state object.
     */
    virtual ~GameState() = default;

    /**
     * @brief Update state each frame.
     */
    virtual void Update() = 0;

    virtual void FixedUpdate() = 0;

    /**
     * @brief Provide pointer to game manager.
     */
    static void ProvideGameManager(GameManager &manager);

    /**
     * @brief Reacts on player collision event.
     */
    virtual void PlayerCollision() = 0;

    /**
     * @brief Inits game state with its initial settings or values.
     */
    virtual void InitGameState() = 0;

    /// Normal state of the game.
    static GameStateNormal normal_;
    /// Reset state of the game.
    static GameStateReset reset_;
    /// Game over state of the game.
    static GameStateOver over_;

protected:

    /// Game Manager object of the game.
    static GameManager *manager_;
};