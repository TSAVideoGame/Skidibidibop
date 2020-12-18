#include "system.h"

Game::ECS::Systems::Manager& Game::ECS::Systems::Manager::get_instance()
{
  static Manager instance;
  return instance;
}

Game::ECS::Systems::Manager::Manager()
{

}

Game::ECS::Systems::Manager::~Manager()
{
  for (System* s : systems)
    delete s;
}
