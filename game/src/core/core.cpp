#include "core.h"
#include "constants.h"
#include "plugins.h"
#include "system.h"
#include "scene.h"

// Temporary
#include "entity.h"
#include "component.h"
#include "render_component.h"

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

// Temporary entities to test out drawing
static Game::ECS::Entity player = Game::ECS::EntityManager::get_instance().create_entity();
#include <iostream>

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

  // TODO: Scenes::Manager should set up void scene by itself
  Scenes::Manager::get_instance().set_scene(Scenes::Manager::get_instance().get_scene<Scenes::Void>());

  // Testing plugins
  Plugins::Manager::get_instance().get_plugin<Plugins::Audio>()->add_music("res/music/TSA_test_1.wav");
  Plugins::Manager::get_instance().get_plugin<Plugins::Audio>()->play_music(0);

  // ECS testing
  ECS::Components::RenderManager* rm = ECS::Components::Manager::get_instance().get_component<ECS::Components::RenderManager>();
  ECS::Components::RenderManager::Instance rmi = rm->add_component(player);

  SDL_Rect src_rect = {0, 6 * 32, 32 ,32};
  rm->set_src_rect(rmi, src_rect);
  SDL_Rect dest_rect = {0, 0, 32, 32};
  rm->set_dest_rect(rmi, dest_rect);
}

/*
 * ========================================
 * Core::close
 * ========================================
 */
void Game::Core::close()
{
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
  Scenes::Manager::get_instance().update();
}

void Game::Core::draw()
{
  renderer->clear();

  Scenes::Manager::get_instance().draw(renderer);

  renderer->present();
}

// Getters / Setters
bool Game::Core::is_running() { return running; }

// Unused functions
Game::Core::Core() {}
Game::Core::~Core() {}
