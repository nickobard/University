#pragma once
#include <vector>
#include "../components/ControllerComponent.hpp"
#include "../components/PlayerController.hpp"
#include "../game_objects/GameObject.hpp"
#include "../game_objects/Pacman.hpp"
#include "../game_objects/Controller.hpp"
#include "GameGraphics.hpp"
#include "GameTime.hpp"
#include "GameLocator.hpp"
#include "GameEvents.hpp"
#include <iostream>
using namespace std;
/**
 * @brief Class which represents the game, starting it, looping and quiting on the users input.
 * 
 */
class Game {
  public:
    // Constructs Game object.
    Game() = default;
    /**
     * @brief Destroy the Game object.
     * 
     * Use gameClose() method to clean the game.
     */
    ~Game();
    // Starts the game - game loop and run until quit.
    void GameStart();
  private:
    // Initialize and loads the game with textures,
    // game objects and other services.
    void GameInit();
    // Initialize game locator with service before game actually starts.
    void InitGameLocator() const;
    // Initialize game objects for the game.
    void InitGameObjects();
    /**
     * @brief Game loop - updates the game every frame.
     * 
     * The heart of the game. Don't break it.
     */
    void GameLoop();
    // Render game and game objects.
    void RenderGame();
    // Prepare all game objctes to show on the screen,
    // rendering them.
    void RenderGameObjects();
    // Updates input events and objects.
    void UpdateGame();
    // Update game mechanics - each object.
    void UpdateGameObjects();
    // Frees all objects and then services.
    void FreeGame();
    // Frees all allocated game objects.
    void FreeGameObjects();
    // Frees game locator with all its runnign services.
    void FreeGameLocator();
    // Game events object - to handle event quiery from user.
    GameEvents events_;
    // Container for all gameActors in the game.
    vector<GameActor *> gameActors_;    
    // Container for all GameControllers in the game.
    vector<Controller *> gameControllers_;
};