#include "core.h"

int main(int argc, char* args[])
{
  const int FPS = 30;
  const int FRAME_DELAY = 1000 / FPS;

  Game::Core::init();

  while (Game::Core::is_running())
  {
    Uint32 frame_start = SDL_GetTicks();

    Game::Core::input();
    Game::Core::update();
    Game::Core::draw();

    int frame_time = SDL_GetTicks() - frame_start;

    while (FRAME_DELAY > frame_time)
    {
      Game::Core::input();
      frame_time = SDL_GetTicks() - frame_start;
    }
  }

  Game::Core::close();

  return 0;
}
