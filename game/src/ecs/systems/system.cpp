#include "system.h"

Game::ECS::Systems::Manager::Manager()
{
  update_functions.reserve(0);
  draw_functions.reserve(0);
}

Game::ECS::Systems::Manager::~Manager()
{

}

void Game::ECS::Systems::Manager::update()
{
  for (void(*f)() : update_functions)
    f();
}

void Game::ECS::Systems::Manager::draw()
{
  for (void(*f)() : draw_functions)
    f();
}

void Game::ECS::Systems::Manager::register_update(void(*f)())
{
  update_functions.push_back(f);
}

void Game::ECS::Systems::Manager::register_draw(void(*f)())
{
  draw_functions.push_back(f);
}
