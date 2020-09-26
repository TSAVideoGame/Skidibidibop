#include "core.h"
#include <SDL2/SDL.h>

bool Game::Core::Core::running = true;
Game::SDL::Window* Game::Core::Core::window;

void Game::Core::Core::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    running = false;

  window = new SDL::Window("Skidibidibop", 0, 0, 960, 640, 0);
}

void Game::Core::Core::close()
{
  delete window;

  SDL_Quit();
}

void Game::Core::Core::input()
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
      {
        running = false;
        break;
      }
    }
  }
}

void Game::Core::Core::update()
{

}

void Game::Core::Core::draw()
{

}
