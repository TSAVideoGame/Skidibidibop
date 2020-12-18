#include "component.h"

Game::ECS::Components::Manager& Game::ECS::Components::Manager::get_instance()
{
  static Manager instance;
  return instance;
}

/*
 * ========================================
 * Constructors / Desctructor
 * ========================================
 */
Game::ECS::Components::Manager::Manager()
{

}

Game::ECS::Components::Manager::~Manager()
{
  for (Component* c : components)
    delete c;
}
