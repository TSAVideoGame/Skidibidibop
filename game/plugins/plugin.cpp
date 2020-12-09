#include "plugin.h"

Game::Plugins::Manager& Game::Plugins::Manager::get_instance()
{
  static Manager instance;
  return instance;
}

Game::Plugins::Manager::Manager()
{

}

Game::Plugins::Manager::~Manager()
{
  for (Plugin* p : plugins)
    delete p;
}
