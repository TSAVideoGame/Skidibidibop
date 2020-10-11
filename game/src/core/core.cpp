#include "core.h"
#include <SDL2/SDL.h>

bool Game::Core::Core::running = true;
Game::Core::States::State Game::Core::Core::state = {Game::Core::States::States::TITLE, {}};
Game::Core::Inputs::Pressed Game::Core::Core::inputs = {false, false, false, false, false, false, false, false};
Game::SDL::Window* Game::Core::Core::window;
Game::SDL::Renderer* Game::Core::Core::renderer;
Game::SDL::Texture* Game::Core::Core::texture;
Game::Core::ManagerManager* Game::Core::Core::manager;

Game::Core::Camera Game::Core::Core::camera = {0, 0};

void Game::Core::Core::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    running = false;

  window = new SDL::Window("Skidibidibop", 0, 0, CONSTANTS.WINDOW.WIDTH, CONSTANTS.WINDOW.HEIGHT, 0);
  renderer = new SDL::Renderer(window);
  texture = new SDL::Texture("res/spritesheet.png", renderer);

  // This is for testing purposes
  state.current = States::States::GAME;
  state.data.game.state = States::Game::States::NORMAL;

  manager = new ManagerManager(renderer);
}

void Game::Core::Core::close()
{
  delete manager;

  delete texture;
  delete renderer;
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
      case SDL_KEYDOWN:
      {
        switch (e.key.keysym.sym)
        {
          case Inputs::UP_KEY:
          {
            inputs.up = true;
            break;
          }
          case Inputs::RIGHT_KEY:
          {
            inputs.right = true;
            break;
          }
          case Inputs::DOWN_KEY:
          {
            inputs.down = true;
            break;
          }
          case Inputs::LEFT_KEY:
          {
            inputs.left = true;
            break;
          }
        }
        break;
      }
      case SDL_KEYUP:
      {
        switch (e.key.keysym.sym)
        {
          case Inputs::UP_KEY:
          {
            inputs.up = false;
            break;
          }
          case Inputs::RIGHT_KEY:
          {
            inputs.right = false;
            break;
          }
          case Inputs::DOWN_KEY:
          {
            inputs.down = false;
            break;
          }
          case Inputs::LEFT_KEY:
          {
            inputs.left = false;
            break;
          }
        }
        break;
      }
    }
  }
}

void Game::Core::Core::update()
{
  manager->update();
}

void Game::Core::Core::draw()
{
  renderer->setDrawColor(0, 0, 0, 255);
  renderer->clear();

  manager->draw();

  renderer->present();
}
