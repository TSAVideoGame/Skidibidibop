#include "render_system.h"
#include "render_component.h"
#include "core.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Render> Game::ECS::Systems::render_system;

void Game::ECS::Systems::Render::draw(SDLW::Renderer* renderer)
{
  Components::RenderManager* rm = Components::Manager::get_instance().get_component<Components::RenderManager>();
  for (std::size_t i = 0; i < rm->data.instances; ++i)
  {
    // Temporary, texture shouldn't be obtained like this
    renderer->copy(Core::get_texture(), &rm->data.src_rect[i], &rm->data.dest_rect[i]);
  }
}
