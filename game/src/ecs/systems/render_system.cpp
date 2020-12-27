#include "render_system.h"
#include "render_component.h"
#include "transform_component.h"
#include "core.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Render> Game::ECS::Systems::render_system;

void Game::ECS::Systems::Render::draw(SDLW::Renderer* renderer)
{
  Components::RenderManager* rm = Components::Manager::get_instance().get_component<Components::RenderManager>();
  Components::TransformManager* tm = Components::Manager::get_instance().get_component<Components::TransformManager>();
  // Loops starts at 1 to skip the null component
  for (std::size_t i = 0; i < rm->data.instances; ++i)
  {
    // Update position if needed
    Components::TransformManager::Instance tmi = tm->get_instance(rm->data.entity[i]);
    if (tmi.index != 0)
    {
      rm->data.dest_rect[i].x = tm->get_offset_x(tmi);
      rm->data.dest_rect[i].y = tm->get_offset_y(tmi);
    }
    // Temporary, texture shouldn't be obtained like this
    renderer->copy(Core::get_texture(), &rm->data.src_rect[i], &rm->data.dest_rect[i]);
  }
}
