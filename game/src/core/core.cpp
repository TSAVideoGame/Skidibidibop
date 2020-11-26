#include "core.h"

/*
 * ========================================
 * Game::Core
 *
 * Handles game loop input, update, and
 * drawing
 * ========================================
 */

// Data members
SDLW::Window* Game::Core::window;
SDLW::Renderer* Game::Core::renderer;
SDLW::Texture* Game::Core::spritesheet;
bool Game::Core::running;

std::vector<Game::Plugins::Plugin*> Game::Core::plugins;

void Game::Core::init()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  
  window = new SDLW::Window("Skidibidbop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, 0);

  running = true;
}

void Game::Core::close()
{
  delete window;

  SDL_Quit(); 
}

void Game::Core::input()
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

void Game::Core::update()
{

}

void Game::Core::draw()
{

}

// Plugin functions
void Game::Core::load_plugins()
{
  plugins.reserve(0);
}

void Game::Core::close_plugins()
{
  for (Plugins::Plugin* p : plugins)
    delete p;
}

// Getters / Setters
bool Game::Core::is_running() { return running; }

// Unused functions
Game::Core::Core() {}
Game::Core::~Core() {}
