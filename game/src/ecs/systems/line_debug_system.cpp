#include "line_debug_system.h"
#include "line_component.h"
#include "camera_system.h"

#include "core.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::LineDebug> Game::ECS::Systems::line_debug_system;

void Game::ECS::Systems::LineDebug::draw(SDLW::Renderer* renderer)
{
  Components::LineManager* lm = Components::Manager::get_instance().get_component<Components::LineManager>();
  Systems::Camera* cs = Systems::Manager::get_instance().get_system<Systems::Camera>();

  for (std::size_t i = 1; i < lm->data.instances; ++i)
  {
    renderer->set_draw_color(255, 255, 255, 255);
    SDL_RenderDrawLine(renderer->get_SDL(),
      static_cast<int>(lm->data.v1_x[i] - cs->get_x()),
      static_cast<int>(lm->data.v1_y[i] - cs->get_y()),
      static_cast<int>(lm->data.v2_x[i] - cs->get_x()),
      static_cast<int>(lm->data.v2_y[i] - cs->get_y())
    );
  }
}