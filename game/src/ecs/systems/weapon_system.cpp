#include "weapon_system.h"
#include "weapon_component.h"
#include "projectile_def_component.h"
#include "projectile_component.h"
#include "render_component.h"
#include "transform_component.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Weapon> weapon_system;

std::vector<Game::ECS::Entity> Game::ECS::Systems::Weapon::weapons;
std::vector<Game::ECS::Entity> Game::ECS::Systems::Weapon::projectiles;

static void bow_arrow_on_create(Game::ECS::Entity e)
{
  Game::ECS::Components::RenderManager* rm = Game::ECS::Components::Manager::get_instance().get_component<Game::ECS::Components::RenderManager>();
  Game::ECS::Components::RenderManager::Instance ri = rm->add_component(e);
  SDL_Rect r = { 96, 64, 32, 32 };
  rm->set_src_rect(ri, r);

  Game::ECS::Components::TransformManager* tm = Game::ECS::Components::Manager::get_instance().get_component<Game::ECS::Components::TransformManager>();
  Game::ECS::Components::TransformManager::Instance ti = tm->add_component(e);
  
  Game::ECS::Components::ProjectileManager* pm = Game::ECS::Components::Manager::get_instance().get_component<Game::ECS::Components::ProjectileManager>();
  Game::ECS::Components::ProjectileManager::Instance pmi = pm->get_instance(e);
  r.x = pm->get_x(pmi);
  r.y = pm->get_y(pmi);
  r.w = 64;
  r.h = 64;
  rm->set_dest_rect(ri, r);

  tm->set_x(ti, pm->get_x(pmi));
  tm->set_y(ti, pm->get_y(pmi));
}

void Game::ECS::Systems::Weapon::init()
{
  Components::WeaponManager* wm = Components::Manager::get_instance().get_component<Components::WeaponManager>();
  Components::ProjectileDefManager* pdm = Components::Manager::get_instance().get_component<Components::ProjectileDefManager>();

  // Bow arrow
  Entity bow_arrow = EntityManager::get_instance().create_entity();
  Components::ProjectileDefManager::Instance bow_pdi = pdm->add_component(bow_arrow);
  pdm->set_damage(bow_pdi, 1);
  pdm->set_status(bow_pdi, 0);
  pdm->set_bounce(bow_pdi, 1);
  pdm->set_create(bow_pdi, bow_arrow_on_create);
  pdm->set_update(bow_pdi, [](int* a, int* b, int* c, int* d, int t) {*b -= 4;});
  pdm->set_destroy(bow_pdi, [](){});
  pdm->set_damage(bow_pdi, 1);
  pdm->set_damage(bow_pdi, 1);
  pdm->set_max_ticks(bow_pdi, 90);

  // Bow
  Entity bow = EntityManager::get_instance().create_entity();

  Components::WeaponManager::Instance bow_wi = wm->add_component(bow);
  wm->set_id(bow_wi, 2);
  wm->set_cooldown(bow_wi, 30);
  wm->set_animation_id(bow_wi, 1 + 3 * 2);
  wm->set_projectile_id(bow_wi, 1);

  weapons.push_back(bow);
}