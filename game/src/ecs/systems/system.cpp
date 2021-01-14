#include "system.h"

Game::ECS::Systems::Manager& Game::ECS::Systems::Manager::get_instance()
{
  static Manager instance;
  return instance;
}

void Game::ECS::Systems::Manager::init()
{
  for (System* s : systems)
    s->init();
}

void Game::ECS::Systems::Manager::quit()
{
  for (System* s : systems)
  {
    s->quit();
    delete s;
  }

}

Game::ECS::Systems::Manager::Manager()
{

}

Game::ECS::Systems::Manager::~Manager()
{
}
