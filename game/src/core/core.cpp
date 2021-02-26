#include "core.h"
#include "constants.h"
#include "plugins.h"
#include "scene.h"
#include "system.h"
#include <cstdint>

#include "test_scene.h"
#include "title_scene.h"

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
bool Game::Core::running = false;
// Input
Game::Input::Data Game::Core::inputs = {false, false, false, false, false, false, false, false, false};
Game::Input::KeyBindings Game::Core::key_bindings;
// State
Game::GameState Game::Core::game_state = Game::GameState::NORMAL;
// Logger
Game::Logger Game::Core::logger("log");
// Resources
SDLW::Texture* Game::Core::spritesheet = nullptr;
std::ifstream Game::Core::map_file;
FFM::Data::Types::Map Game::Core::map_helper;
Game::Camera Game::Core::camera = {0, 0};
std::uint32_t Game::Core::current_chunk = 0;

/*
 * ========================================
 * Core::init
 *
 * Initializes SDL, creates some objects
 * ========================================
 */
void Game::Core::init()
{
  logger.enable(Logger::LOG | Logger::ERROR);
  logger.log(Logger::LOG, "Testing log");
  logger.log(Logger::LOG, "Testing log again");

  // Initialize SDL and subsystems
  if (SDL_Init(0))
  {
    logger.log(Logger::ERROR, "Could not initialize SDL");
    std::exit(-1);
  }

  if(SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
  {
    logger.log(Logger::ERROR, "Could not initialize SDL Subsystems");
    std::exit(-1);
  }
 
  // Initialize SDLW objects
  // TODO: Make sure all of these do not return nullptrs
  window = new SDLW::Window("Skidibidbop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Constants.Window.width, Constants.Window.height, 0);
  renderer = new SDLW::Renderer(window);
  spritesheet = new SDLW::Texture("res/spritesheet.png", renderer);

  running = true;

  // Use the test scene
  Scenes::Manager::get_instance().set_scene(Scenes::Manager::get_instance().get_scene<Scenes::Title>());

  // Init systems
  ECS::Systems::Manager::get_instance().init();

  // Testing plugins
  for (int i = 1; i <= 24; ++i)
    Plugins::Manager::get_instance().get_plugin<Plugins::Audio>()->add_music("res/music/TSA_test_" + std::to_string(i) +".wav");
  Plugins::Manager::get_instance().get_plugin<Plugins::Audio>()->play_music(23);
}

/*
 * ========================================
 * Core::close
 * ========================================
 */
void Game::Core::close()
{
  ECS::Systems::Manager::get_instance().quit();

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
      case SDL_KEYDOWN:
      {
        SDL_Keycode key = e.key.keysym.sym;

        if (key == key_bindings.up)
          inputs.up = true;
        if (key == key_bindings.right)
          inputs.right = true;
        if (key == key_bindings.down)
          inputs.down = true;
        if (key == key_bindings.left)
          inputs.left = true;
        if (key == key_bindings.slot_a)
          inputs.slot_a = true;
        if (key == key_bindings.slot_b)
          inputs.slot_b = true;
        if (key == key_bindings.slot_c)
          inputs.slot_c = true;
        if (key == key_bindings.attack)
          inputs.attack = true;
        if (key == key_bindings.pause)
          inputs.pause = true;

        break;
      }
      case SDL_KEYUP:
      {
        SDL_Keycode key = e.key.keysym.sym;

        if (key == key_bindings.up)
          inputs.up = false;
        if (key == key_bindings.right)
          inputs.right = false;
        if (key == key_bindings.down)
          inputs.down = false;
        if (key == key_bindings.left)
          inputs.left = false;
        if (key == key_bindings.slot_a)
          inputs.slot_a = false;
        if (key == key_bindings.slot_b)
          inputs.slot_b = false;
        if (key == key_bindings.slot_c)
          inputs.slot_c = false;
        if (key == key_bindings.attack)
          inputs.attack = false;
        if (key == key_bindings.pause)
          inputs.pause = false;

        break;
      }
      // TODO: Mose button input
      case SDL_MOUSEBUTTONDOWN:
      {
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        break;
      }
    }
  }

  SDL_GetMouseState(&inputs.mouse_x, &inputs.mouse_y);
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
const Game::Input::Data Game::Core::get_inputs() { return inputs; }
Game::GameState Game::Core::get_state() { return game_state; }
// Unused functions
Game::Core::Core() {}
Game::Core::~Core() {}