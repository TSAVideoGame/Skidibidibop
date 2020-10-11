#include "core_manager_manager.h"
#include "map.h"
#include "data.h"

Game::Core::ManagerManager::ManagerManager(SDL::Renderer* renderer) : Manager()
{
  objects.push_back(new Map::Manager(renderer, Data::Save::load("res/test.sbbd").map));
}

void Game::Core::ManagerManager::update()
{
  Manager::update();
}
