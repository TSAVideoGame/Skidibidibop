#include "core.h"
#include "constants.h"

/*
 * ========================================
 * Game::Core
 *
 * Handles game loop input, update, and
 * drawing
 * ========================================
 */

/*
 * ========================================
 * Data members
 * ========================================
 */
// Basic
SDLW::Window* Game::Core::window = nullptr;
SDLW::Renderer* Game::Core::renderer = nullptr;
SDLW::Texture* Game::Core::spritesheet = nullptr;
bool Game::Core::running = false;

// Plugins
std::vector<Game::Plugins::Plugin*> Game::Core::plugins;

// ECS
Game::ECS::Components::Manager* Game::Core::components = nullptr;
Game::ECS::EntityManager* Game::Core::entity_manager = nullptr;

/*
 * ========================================
 * Core::init
 * ========================================
 */
void Game::Core::init()
{
  SDL_Init(0);
  SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  
  window = new SDLW::Window("Skidibidbop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants.Window.width, Constants.Window.height, 0);
  renderer = new SDLW::Renderer(window);
  spritesheet = new SDLW::Texture("res/spritesheet.png", renderer);

  running = true;

  load_plugins();

  // Testing plugins
  get_plugin<Plugins::Audio>()->play_music(0);

  components = new ECS::Components::Manager();
  entity_manager = new ECS::EntityManager();
}

/*
 * ========================================
 * Core::close
 * ========================================
 */
void Game::Core::close()
{
  delete entity_manager;
  delete components;

  close_plugins();

  delete spritesheet;
  delete renderer;
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
