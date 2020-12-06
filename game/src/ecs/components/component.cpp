#include "component.h"
#include "transform_component.h"
#include "render_component.h"

std::vector<Game::ECS::Components::Component*> Game::ECS::Components::Manager::components;

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
