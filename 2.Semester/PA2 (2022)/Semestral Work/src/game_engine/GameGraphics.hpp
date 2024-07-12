#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

constexpr size_t SCREEN_HEIGHT = 1080;
constexpr size_t SCREEN_WIDTH = 1080;

/**
 * @brief Class that initialize overall graphics for the game.
 * Initialize window, renderer, and clearing and rendering on the screen.
 */
class GameGraphics {

public:

    /**
     * @brief Construct a new Game Graphics object.
     * Initiates graphics of the game - window, renderer etc.
     */
    GameGraphics();

    /**
     * @brief Destroy game graphics object.
     */
    ~GameGraphics();

    /**
     * @brief Clear the screen from all rendered objects.
     */
    void ClearRender();

    /**
     * @brief Shows all current rendered game objects on the screen.
     */
    void RenderGame();

    /// Gets the renderer.
    inline SDL_Renderer *GetRenderer();

private:

    /**
     * @brief Initialize SDL and create window with renderer.
     * Sets renderDrawColor to black.
     */
    void InitGameGraphics();

    /**
     * @brief Initialize SDL libraries.
     * @return true if success.
     */
    static bool InitSDL();

    /**
     * @brief Inits IMG library and returns true on success.
     * @return true if success.
     */
    static bool InitIMG();

    /**
     * @brief Sets different settings for SDL.
     * Sets render quality to anisotropic linear filtration
     */
    static void SetSDLSettings();

    /**
     * @brief Creates game window and renderer.
     * @return true if success.
     */
    bool CreateGameGraphics();

    /**
     * @brief Initializes and creates game window.
     * @return true if success.
     */
    bool CreateGameWindow();

    /**
     * @brief Initializes and creates game renderer for current window.
     * @return true if success.
     */
    bool CreateGameRenderer();

    /**
     * @brief Destroy window and renderer and quits SDL.
     */
    void QuitGameGraphics();

    /**
     * @brief Set the window renderer's default color to white.
     */
    void SetScreenBackgroundWhite();

    /**
     * @brief Set the window renderer's default color to black.
     */
    void SetScreenBackgroundBlack();

    /// Represents game window.
    SDL_Window *window_;
    /// Represents game renderer for the current window.
    SDL_Renderer *renderer_;

};

inline SDL_Renderer *GameGraphics::GetRenderer() {
    return renderer_;
}