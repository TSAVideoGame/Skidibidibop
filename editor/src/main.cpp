#include "window.h"
#include <SDL2/SDL_ttf.h>

int main(int argc, char* args[])
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();

  Editor::Window window;

  while (window.isRunning())
  {
    window.input();
    window.draw();
    window.update();
  }

  TTF_Quit();
  SDL_Quit();

  return 0;
}
