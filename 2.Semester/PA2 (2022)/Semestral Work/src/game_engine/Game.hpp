#pragma once

#include <vector>
#include <iostream>

using namespace std;

#include "../components/ControllerComponent.hpp"
#include "../components/PlayerController.hpp"
#include "../components/AI_components/AIComponent.hpp"
#include "../game_objects/GameObject.hpp"
#include "../game_objects/Pacman.hpp"
#include "../game_objects/Ghost.hpp"
#include "../game_objects/Controller.hpp"
#include "GameGraphics.hpp"
#include "GameTime.hpp"
#include "GameEvents.hpp"
#include "../UI/Canvas.hpp"


/**
 * @brief Class which represents the game, initializing, starting,
 * updating, rendering and quiting the game.
 */
class Game {

public:

    /**
     * @brief Constructs Game object.
     */
    Game() = default;

    /**
     * @brief Destroy the Game object.
     * Use gameClose() method to clean the game.
     */
    ~Game();

    /**
     * @brief Starts the game - game loop and run until quit.
     */
    void GameStart();

    /**
     * @brief Quits game.
     */
    void QuitGame();

    /// Container for all GameControllers in the game.
    vector<Controller *> gameControllers_;

private:

    /**
     * @brief Initializes and loads the game with textures,
     * game objects and other services from game locator.
     */
    void GameInit();

    /**
     * @brief Initialize game locator with services before game actually starts.
     */
    void InitGameLocator();

    /**
     * @brief Initialize game objects for the game.
     */
    void InitGameObjects();

    /**
     * @brief Game loop - updates the game every frame.
     * The heart of the game. Don't break it.
     */
    void GameLoop();

    /**
     * @brief Render game and game objects.
     */
    void RenderGame();

    /**
     * @brief Prepare all game objctes to show on the screen, rendering them.
     */
    void RenderGameObjects();

    /**
     * @brief Updates input events and objects.
     */
    void UpdateGame();

    void FixedUpdateGame();

    /**
     * @brief Update game mechanics - each object.
     */
    void UpdateGameObjects();

    void FixedUpdateGameObject();

    /**
     * @brief Frees all allocated game objects.
     */
    void FreeGameObjects();

    /// Game events object - to handle event queue from user.
    GameEvents events_;
    /// Container for all gameActors in the game.
    vector<GameActor *> gameActors_;
    vector<UIElement *> UIElements_;
};