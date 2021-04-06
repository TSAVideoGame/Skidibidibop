#include "projectile_system.h"
#include "projectile_component.h"
#include "projectile_def_component.h"
#include "transform_component.h"
#include "render_component.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Projectile> projectile_system;

void Game::ECS::Systems::Projectile::update()
{
  Components::ProjectileManager* pm = ECS::Components::Manager::get_instance().get_component<Components::ProjectileManager>();
  Components::ProjectileDefManager* pdm = ECS::Components::Manager::get_instance().get_component<Components::ProjectileDefManager>();

  for (std::uint32_t i = 1; i < pm->data.instances; ++i)
  {
    Components::ProjectileManager::Instance pmi = pm->get_instance(pm->data.entity[i]);
    Components::ProjectileDefManager::Instance pdmi = pdm->get_instance(pm->data.projectile_def[i]);

    if (++pm->data.ticks[i] >= pdm->get_max_ticks(pdmi))
    {
      // Delete render component
      Components::RenderManager* rm = ECS::Components::Manager::get_instance().get_component<Components::RenderManager>();
      Components::RenderManager::Instance rmi = rm->get_instance(pm->data.entity[i]);
      if (rmi.index != 0)
      {
        rm->destroy_component(rmi);
      }

      // Delete transform component
      Components::TransformManager* tm = ECS::Components::Manager::get_instance().get_component<Components::TransformManager>();
      Components::TransformManager::Instance ti = tm->get_instance(pm->data.entity[i]);
      if (ti.index != 0)
      {
        tm->destroy_component(ti);
      }

      // Delete projectile
      pm->destroy_component(pmi);
      EntityManager::get_instance().destory_entity(pm->data.entity[i]);

      continue;
    }

    // Move function
    if (pm->data.direction[i] == 0)
    {
      pdm->get_update(pdmi)(pm->data.x + i, pm->data.y + i, pm->data.w + i, pm->data.h + i, pm->data.ticks[i]);
    }

    Components::TransformManager* tm = ECS::Components::Manager::get_instance().get_component<Components::TransformManager>();
    Components::TransformManager::Instance ti = tm->get_instance(pm->data.entity[i]);
    if (ti.index != 0)
    {
      tm->set_x(ti, pm->data.x[i]);
      tm->set_y(ti, pm->data.y[i]);
    }
  }
}
