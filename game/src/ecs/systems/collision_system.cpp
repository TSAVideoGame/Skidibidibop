#include "collision_system.h"
#include "collision_component.h"
#include "transform_component.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Collision> Game::ECS::Systems::collision_system;

void Game::ECS::Systems::Collision::update()
{

}

Game::ECS::Systems::Collision::AABB Game::ECS::Systems::Collision::get_AABB(Entity entity)
{
  AABB hitbox;

  Components::CollisionManager* cm = Components::Manager::get_instance().get_component<Components::CollisionManager>(); 
  Components::CollisionManager::Instance cmi = cm->get_instance(entity);
  Components::TransformManager* tm = Components::Manager::get_instance().get_component<Components::TransformManager>(); 
  Components::TransformManager::Instance tmi = tm->get_instance(entity);

  hitbox.x = tm->get_x(tmi) + cm->get_offset_x(cmi);
  hitbox.y = tm->get_y(tmi) + cm->get_offset_y(cmi);
  hitbox.w = cm->get_width(cmi);
  hitbox.h = cm->get_height(cmi);
  
  return hitbox;
}
