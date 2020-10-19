#include "core.h"

int main(int argc, char* args[])
{
  const int FPS = 30;
  const int FRAME_DELAY = 1000 / FPS;

  Game::Core::Core::init();

  while (Game::Core::Core::isRunning())
  {
    Uint32 frameStart = SDL_GetTicks();

    Game::Core::Core::input();
    Game::Core::Core::update();
    Game::Core::Core::draw();

    int frameTime = SDL_GetTicks() - frameStart;

    while (FRAME_DELAY > frameTime)
    {
      Game::Core::Core::input();
      frameTime = SDL_GetTicks() - frameStart;
    }
  }

  Game::Core::Core::close();

  return 0;
}
