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

Game::ECS::Components::Manager Game::Core::components;

void Game::Core::init()
{
  SDL_Init(0);
  SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  
  window = new SDLW::Window("Skidibidbop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, 0);

  running = true;

  load_plugins();

  get_plugin<Plugins::Audio>()->play_music(0);
}

void Game::Core::close()
{
  close_plugins();

  delete window;

  SDL_QuitSubSystem(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
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
  plugins.reserve(1);

  get_plugin<Plugins::Audio>()->add_music("res/music/TSA_test_1.wav");
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
