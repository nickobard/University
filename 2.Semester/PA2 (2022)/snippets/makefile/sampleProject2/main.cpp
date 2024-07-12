#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

int main () {
  cout << "Hello world" << endl;
  SDL_Init(SDL_INIT_AUDIO);
  SDL_Quit();
  return 0;
}