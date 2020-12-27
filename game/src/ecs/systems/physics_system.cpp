#include "physics_system.h"
#include "physics_component.h"
#include "transform_component.h"
#include <cmath>

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Physics> physics_system;

void Game::ECS::Systems::Physics::update()
{
  Components::PhysicsManager* pm = Components::Manager::get_instance().get_component<Components::PhysicsManager>();
  Components::TransformManager* tm = Components::Manager::get_instance().get_component<Components::TransformManager>();
  // Loop starts at 1 to skip the null component
  for (std::size_t i = 1; i < pm->data.instances; ++i)
  {
    // Update velocites
    pm->data.x_vel[i] += pm->data.x_accel[i];
    if (std::abs(pm->data.x_vel[i]) > pm->data.max_x_vel[i])
      pm->data.x_vel[i] > 0 ? pm->data.x_vel[i] = pm->data.max_x_vel[i] : pm->data.x_vel[i] = -pm->data.max_x_vel[i];

    pm->data.y_vel[i] += pm->data.y_accel[i];
    if (std::abs(pm->data.y_vel[i]) > pm->data.max_y_vel[i])
      pm->data.y_vel[i] > 0 ? pm->data.y_vel[i] = pm->data.max_y_vel[i] : pm->data.y_vel[i] = -pm->data.max_y_vel[i];

    // Move positions
    Components::TransformManager::Instance ti = tm->get_instance(pm->data.entity[i]);
    if (ti.index != 0)
    {
      tm->set_offset_x(ti, tm->get_offset_x(ti) + static_cast<int>(pm->data.x_vel[i]));
      tm->set_offset_y(ti, tm->get_offset_y(ti) + static_cast<int>(pm->data.y_vel[i]));
    }
  }
}
