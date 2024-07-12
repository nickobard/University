
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

using namespace std;

int main (){

  // string * leak1 = new string("Leak!");


  // SDL_Init(SDL_INIT_EVERYTHING);
  // SDL_Quit();

  if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    cout << SDL_GetError() << endl;
  SDL_Window * window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, 0 );

  string word;
  while (word != "stop"){
    cin >> word;
  }

  // string * leak2 = new string("Leak!");

  SDL_DestroyWindow(window);
  // SDL_VideoQuit();
  SDL_Quit();

  return 0;
}