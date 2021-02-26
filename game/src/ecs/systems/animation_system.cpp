#include "animation_system.h"
#include "animation_component.h"
#include "render_component.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Animation> Game::ECS::Systems::animation_system;


void Game::ECS::Systems::Animation::update()
{
  Components::AnimationManager* am = Components::Manager::get_instance().get_component<Components::AnimationManager>();
  Components::RenderManager* rm = Components::Manager::get_instance().get_component<Components::RenderManager>();

  for (std::size_t i = 1; i < am->data.instances; ++i)
  {
    // Increment Frame
    // Check if animation needs to be updated
    if (++am->data.frames[i] == am->data.animations[i][am->data.state[i]].animation_data[am->data.animation_pos[i]].frames)
    {
      am->data.frames[i] = 0;
      if (am->data.animation_pos[i] == am->data.animations[i][am->data.state[i]].animation_data.size() - 1)
      {
        am->data.animation_pos[i] = 0;
      }
      else
      {
        ++am->data.animation_pos[i];
      }

      Components::RenderManager::Instance rmi = rm->get_instance(am->data.entity[i]);
      if (rmi.index != 0)
      {
        SDL_Rect new_rect = rm->get_src_rect(rmi);
        new_rect.x = am->data.animations[i][am->data.state[i]].animation_data[am->data.animation_pos[i]].sprite_id * 32;
        rm->set_src_rect(rmi, new_rect);
      }
    }
  }
}