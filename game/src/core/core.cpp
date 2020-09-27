#include "core.h"
#include <SDL2/SDL.h>

#include "map.h"
#include "data.h"

bool Game::Core::Core::running = true;
Game::Core::State Game::Core::Core::state = State::GAME;
Game::SDL::Window* Game::Core::Core::window;
Game::SDL::Renderer* Game::Core::Core::renderer;
Game::SDL::Texture* Game::Core::Core::texture;

Game::Core::Camera Game::Core::Core::camera = {0, 0};

static Game::Map::Manager* mapManager;

void Game::Core::Core::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    running = false;

  window = new SDL::Window("Skidibidibop", 0, 0, CONSTANTS.WINDOW.WIDTH, CONSTANTS.WINDOW.HEIGHT, 0);
  renderer = new SDL::Renderer(window);
  texture = new SDL::Texture("res/spritesheet.png", renderer);

  mapManager = new Map::Manager(renderer, Data::Save::load("res/test.sbbd").map);
}

void Game::Core::Core::close()
{
  delete mapManager;

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
      // Bad code, input object/struct should be made to deal with inputs
      case SDL_KEYDOWN:
      {
        switch (e.key.keysym.sym)
        {
          case SDLK_w:
          {
            camera.y -= 8;
            break;
          }
          case SDLK_s:
          {
            camera.y += 8;
            break;
          }
          case SDLK_a:
          {
            camera.x -= 8;
            break;
          }
          case SDLK_d:
          {
            camera.x += 8;
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

}

void Game::Core::Core::draw()
{
  renderer->setDrawColor(0, 0, 0, 255);
  renderer->clear();

  mapManager->draw();

  renderer->present();
}
