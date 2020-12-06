#include "component.h"
#include "transform_component.h"
#include "render_component.h"

Game::ECS::Components::Manager::Manager()
{
  components.reserve(2);
  get_component<TransformManager>();
  get_component<RenderManager>();
}

Game::ECS::Components::Manager::~Manager()
{
  for (Component* c : components)
    delete c;
}
