#include "GameGraphics.hpp"

using namespace std;

GameGraphics::GameGraphics()
        : window_(nullptr), renderer_(nullptr) {
    InitGameGraphics();
}

GameGraphics::~GameGraphics() {
    QuitGameGraphics();
}

void GameGraphics::QuitGameGraphics() {
    // Complete quit of SDL - when the game is closing
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GameGraphics::InitGameGraphics() {
    if (!InitSDL()) {
        cerr << "Could not initialize SDL." << endl;
        throw exception();
    }
    SetSDLSettings();
    if (!CreateGameGraphics()) {
        cerr << "Could not create window or renderer." << endl;
        throw exception();
    }
}

void GameGraphics::RenderGame() {

    // Render all current objects from buffer to render
    SDL_RenderPresent(renderer_);
}

void GameGraphics::ClearRender() {
    // Clear screen with all rendered objects to prepare render new
    SDL_RenderClear(renderer_);
}

void GameGraphics::SetScreenBackgroundWhite() {
    SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
}

void GameGraphics::SetScreenBackgroundBlack() {
    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);
}

void GameGraphics::SetSDLSettings() {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        cerr << "Warning: Linear texture filtering not enabled!" << endl;
}

bool GameGraphics::InitIMG() {
    int imgFlags = IMG_INIT_PNG;
    return IMG_Init(imgFlags) & imgFlags;
}

bool GameGraphics::InitSDL() {
    // Initialize the SDL system - video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    // Initialize libraries (dll) for PNG images
    if (!InitIMG()) {
        cerr << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << endl;
        return false;
    }

    if (TTF_Init() != 0) {
        cerr << "SDL_ttf could not initialize! SDL_ttf Error:" << TTF_GetError() << endl;
        return false;
    }

    return true;
}

bool GameGraphics::CreateGameGraphics() {
    if (!CreateGameWindow() || !CreateGameRenderer())
        return false;
    SetScreenBackgroundBlack();
    return true;
}

bool GameGraphics::CreateGameWindow() {

    window_ = SDL_CreateWindow("Pacman Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window_ == nullptr) {
        cerr << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

bool GameGraphics::CreateGameRenderer() {
    // Create renderer for the opened window
    // Set VSYNC for renderer and use of GPU renderer
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ == nullptr) {
        cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}