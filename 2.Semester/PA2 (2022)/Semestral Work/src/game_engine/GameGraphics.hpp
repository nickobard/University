#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

constexpr int SCREEN_HEIGHT = 1000;
constexpr int SCREED_WIDTH = 1000;
/**
 * @brief Class that initialize overall graphics for the game.
 * 
 * Initialize window, renderer, and clearing and rendering on the screen.
 * 
 */
class GameGraphics {
  public:
    // Construct a new Game Graphics object.
    // Sets window and renderer with nullptr. Then initiates
    // graphics of the game.
    GameGraphics();
    // Destroy with calling QuitGameGraphics();
    ~GameGraphics();
    // Clear the screen from all rendered objects 
    // with background color.
    void ClearRender();
    // Shows all current rendererd game objects with current
    // renderer.
    void RenderGame();
    // Gets the renderer of the Game Graphics service.
    inline SDL_Renderer * GetRenderer();
  private:
    /**
     * @brief Initialize SDL and create window with renderer.
     * 
     * Sets renderDrawColor to black. Expects that that this isn't changed.
     */
    void InitGameGraphics();
    // Initialize SDL libraries.
    bool InitSDL() const;
    // Inits IMG library and returns true on success.
    bool InitIMG() const;
    // Sets different settigns for SDL.
	  // Set render quality to anizotrophic linear filtration
    void SetSDLSettings() const;
    // Creates game window and renderer.
    bool CreateGameGraphics();
    // Initializes and creates game window.
    bool CreateGameWindow();
    // Initializes and creates game renderer for current window.
    bool CreateGameRenderer();
    // Destroy window and renderer and quit SDL
    void QuitGameGraphics();
    // Set the window renderer to white color.
    void SetScreenBackgroundWhite();
    // Set the window renderer to black color.
    void SetScreenBackgroundBlack();
    // Represents game window.
    SDL_Window * window_;
    // Represents game renderer for the current window.
    SDL_Renderer * renderer_;

};

inline
SDL_Renderer * GameGraphics::GetRenderer(){
  return renderer_;
}