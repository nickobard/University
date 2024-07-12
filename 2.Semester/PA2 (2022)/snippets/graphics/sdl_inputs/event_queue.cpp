#include "SDL2/SDL.h"
#include <unistd.h>
#include <iostream>
using namespace std;

static constexpr int SCREEN_HEIGHT = 1000;
static constexpr int SCREED_WIDTH = 1000;


int main () {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window * window = SDL_CreateWindow ("Pacman Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREED_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  bool quit = false;
  char dummy;
  SDL_Event e;

    int x = 0;
  while (!quit){
    //cout << "Proceed?" << endl;
    //cin >> dummy;
    //if (dummy == '-')
      //quit = true;

    while (SDL_PollEvent(&e) != 0){
      if (e.type = SDL_KEYDOWN ){
        switch( e.key.keysym.sym){
          case SDLK_q: cout << "q" << endl; break;
          case SDLK_w: cout << "w" << endl; break;
          // default:cout << "else code" << endl; break;
        }
      }
    }
    const uint8_t * keys = SDL_GetKeyboardState(nullptr);
    if ( keys[SDL_SCANCODE_G])
      cout << "G" << endl;
    if ( keys[SDL_SCANCODE_H])
      cout << "H" << endl;
    cout << "loop! " << ++x << endl;
    sleep(1);

  }
  SDL_DestroyWindow(window);
  SDL_Quit();
}