#include "component.h"
#include "transform_component.h"

Game::ECS::Components::Manager::Manager()
{
  components.reserve(1);
  get_component<TransformManager>();
}

Game::ECS::Components::Manager::~Manager()
{
  for (Component* c : components)
    delete c;
}
