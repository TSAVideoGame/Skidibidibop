#include "test_scene.h"
#include "entity.h"
#include "transform_component.h"
#include "render_component.h"
#include "render_system.h"
#include "physics_component.h"
#include "physics_system.h"
#include "map_system.h"
#include "camera_system.h"
#include "menu_system.h"
#include "core.h"
#include "constants.h"
#include "direction_component.h"
#include "animation_component.h"
#include "animation_system.h"
#include "collision_component.h"
#include "line_debug_system.h"
#include "collision_system.h"
#include "weapon_system.h"
#include "inventory_system.h"
#include "weapon_component.h"
#include "projectile_component.h"
#include "projectile_def_component.h"
#include "projectile_system.h"
#include "weapon_system.h"

static Game::ECS::Entity player = Game::ECS::EntityManager::get_instance().get_null();
static bool paused = false;

Game::Scenes::Manager::RegisterScene<Game::Scenes::TestScene> test_scene;

Game::Scenes::TestScene::TestScene()
{
  // Set Map resources
  Core::map_file.close();
  Core::map_file.open("res/map.ffmf", std::ifstream::binary);
  std::ifstream f("res/map.ffmfd", std::ifstream::binary);
  Core::map_helper.load(f);
  f.close();
  // Get pointers to components
  ECS::Components::TransformManager* tm = ECS::Components::Manager::get_instance().get_component<ECS::Components::TransformManager>();
  ECS::Components::RenderManager* rm = ECS::Components::Manager::get_instance().get_component<ECS::Components::RenderManager>();
  ECS::Components::PhysicsManager* pm = ECS::Components::Manager::get_instance().get_component<ECS::Components::PhysicsManager>();
  ECS::Components::DirectionManager* dm = ECS::Components::Manager::get_instance().get_component<ECS::Components::DirectionManager>();
  ECS::Components::CollisionManager* cm = ECS::Components::Manager::get_instance().get_component<ECS::Components::CollisionManager>();

  // Set up the player
  player = Game::ECS::EntityManager::get_instance().create_entity();

  ECS::Components::TransformManager::Instance tmi = tm->add_component(player);

  tm->set_x(tmi, 800 * 10 + 454);
  tm->set_y(tmi, 800 * 14 + 468);
  tm->set_y(tmi, 800 * 14 + 468);
  
  ECS::Components::RenderManager::Instance rmi = rm->add_component(player);

  SDL_Rect src_rect = {24 * 32, 3 * 32, 32, 32};
  rm->set_src_rect(rmi, src_rect);
  SDL_Rect dest_rect = {0, 0, 64, 64};
  rm->set_dest_rect(rmi, dest_rect);

  ECS::Components::PhysicsManager::Instance pmi = pm->add_component(player);

  pm->set_x_vel(pmi, 0);
  pm->set_y_vel(pmi, 0);
  pm->set_x_accel(pmi, 0);
  pm->set_y_accel(pmi, 0);
  pm->set_max_x_vel(pmi, 8);
  pm->set_max_y_vel(pmi, 8);

  dm->set_direction(player, 0);

  ECS::Components::CollisionManager::Instance cmi = cm->add_component(player);

  cm->set_offset_x(cmi, 0);
  cm->set_offset_y(cmi, 0);
  cm->set_width(cmi, 64);
  cm->set_height(cmi, 64);

  // Player animations
  // TODO: Move animations to a different file and include it or something
  ECS::Components::AnimationManager* am = ECS::Components::Manager::get_instance().get_component<ECS::Components::AnimationManager>();
  ECS::Components::AnimationManager::Instance ami = am->add_component(player);

  am->set_state(ami, 0);

  std::vector<ECS::Components::AnimationManager::Animation> player_animations;

  ECS::Components::AnimationManager::Animation player_idle;
  player_idle.animation_data.reserve(3);
  player_idle.animation_data.push_back({0, 9});
  player_idle.animation_data.push_back({1, 9});
  player_idle.animation_data.push_back({2, 9});

  ECS::Components::AnimationManager::Animation player_run;
  player_run.animation_data.reserve(6);
  player_run.animation_data.push_back({3, 4});
  player_run.animation_data.push_back({4, 4});
  player_run.animation_data.push_back({5, 4});
  player_run.animation_data.push_back({6, 4});
  player_run.animation_data.push_back({7, 4});
  player_run.animation_data.push_back({8, 4});

  // Axe animations
  ECS::Components::AnimationManager::Animation player_axe_idle;
  player_axe_idle.animation_data.reserve(9);
  player_axe_idle.animation_data.push_back({  9, 9 });
  player_axe_idle.animation_data.push_back({ 10, 9 });
  player_axe_idle.animation_data.push_back({ 11, 9 });

  ECS::Components::AnimationManager::Animation player_axe_run;
  player_axe_run.animation_data.reserve(6);
  player_axe_run.animation_data.push_back({ 12, 4 });
  player_axe_run.animation_data.push_back({ 13, 4 });
  player_axe_run.animation_data.push_back({ 14, 4 });
  player_axe_run.animation_data.push_back({ 15, 4 });
  player_axe_run.animation_data.push_back({ 16, 4 });
  player_axe_run.animation_data.push_back({ 17, 4 });

  ECS::Components::AnimationManager::Animation player_axe_attack;
  player_axe_attack.animation_data.reserve(9);
  player_axe_attack.animation_data.push_back({ 18, 4 });
  player_axe_attack.animation_data.push_back({ 19, 4 });
  player_axe_attack.animation_data.push_back({ 20, 4 });
  player_axe_attack.animation_data.push_back({ 21, 2 });
  player_axe_attack.animation_data.push_back({ 22, 2 });
  player_axe_attack.animation_data.push_back({ 23, 2 });

  // Bow animations
  ECS::Components::AnimationManager::Animation player_bow_idle;
  player_bow_idle.animation_data.reserve(9);
  player_bow_idle.animation_data.push_back({24, 9});
  player_bow_idle.animation_data.push_back({25, 9});
  player_bow_idle.animation_data.push_back({26, 9});

  ECS::Components::AnimationManager::Animation player_bow_run;
  player_bow_run.animation_data.reserve(6);
  player_bow_run.animation_data.push_back({ 27, 4 });
  player_bow_run.animation_data.push_back({ 28, 4 });
  player_bow_run.animation_data.push_back({ 29, 4 });
  player_bow_run.animation_data.push_back({ 30, 4 });
  player_bow_run.animation_data.push_back({ 31, 4 });
  player_bow_run.animation_data.push_back({ 32, 4 });

  ECS::Components::AnimationManager::Animation player_bow_attack;
  player_bow_attack.animation_data.reserve(9);
  player_bow_attack.animation_data.push_back({ 33, 2 });
  player_bow_attack.animation_data.push_back({ 34, 2 });
  player_bow_attack.animation_data.push_back({ 35, 2 });
  player_bow_attack.animation_data.push_back({ 36, 2 });
  player_bow_attack.animation_data.push_back({ 37, 2 });
  player_bow_attack.animation_data.push_back({ 38, 2 });
  player_bow_attack.animation_data.push_back({ 39, 2 });
  player_bow_attack.animation_data.push_back({ 40, 2 });
  player_bow_attack.animation_data.push_back({ 41, 2 });

  // Bow animations
  ECS::Components::AnimationManager::Animation player_axe_bow_idle;
  player_axe_bow_idle.animation_data.reserve(9);
  player_axe_bow_idle.animation_data.push_back({ 42, 9 });
  player_axe_bow_idle.animation_data.push_back({ 43, 9 });
  player_axe_bow_idle.animation_data.push_back({ 44, 9 });

  ECS::Components::AnimationManager::Animation player_axe_bow_run;
  player_axe_bow_run.animation_data.reserve(6);
  player_axe_bow_run.animation_data.push_back({ 45, 4 });
  player_axe_bow_run.animation_data.push_back({ 46, 4 });
  player_axe_bow_run.animation_data.push_back({ 47, 4 });
  player_axe_bow_run.animation_data.push_back({ 48, 4 });
  player_axe_bow_run.animation_data.push_back({ 49, 4 });
  player_axe_bow_run.animation_data.push_back({ 50, 4 });

  ECS::Components::AnimationManager::Animation player_axe_bow_attack;
  player_axe_bow_attack.animation_data.reserve(9);
  player_axe_bow_attack.animation_data.push_back({ 51, 2 });
  player_axe_bow_attack.animation_data.push_back({ 52, 2 });
  player_axe_bow_attack.animation_data.push_back({ 53, 2 });
  player_axe_bow_attack.animation_data.push_back({ 54, 2 });
  player_axe_bow_attack.animation_data.push_back({ 55, 2 });
  player_axe_bow_attack.animation_data.push_back({ 56, 2 });
  player_axe_bow_attack.animation_data.push_back({ 57, 2 });
  player_axe_bow_attack.animation_data.push_back({ 51, 2 });

  player_animations.push_back(player_idle);
  player_animations.push_back(player_run);
  player_animations.push_back(player_run); // Fake attack animation for x3 alignment

  player_animations.push_back(player_axe_idle);
  player_animations.push_back(player_axe_run);
  player_animations.push_back(player_axe_attack);

  player_animations.push_back(player_bow_idle);
  player_animations.push_back(player_bow_run);
  player_animations.push_back(player_bow_attack);

  player_animations.push_back(player_axe_bow_idle);
  player_animations.push_back(player_axe_bow_run);
  player_animations.push_back(player_axe_bow_attack);

  am->set_animations(ami, player_animations);
}

Game::Scenes::TestScene::~TestScene()
{
  
}

static int camera_move_x = 0;
static int camera_move_y = 0;
static int run_frames = 0; // Don't immediately return to idle animation
static int cooldown = 0; // Cooldown must be 0 to use
static bool attacking = false;
static int attacking_i = 0; // attack iteration
static int weapon = 0;
void Game::Scenes::TestScene::update()
{
  Input::Data in = Core::get_inputs();
  static bool prev_frame_pause_key = false;

  if (in.pause)
  {
    if (!prev_frame_pause_key)
    {
      paused = !paused;
      prev_frame_pause_key = true;
    }
  }
  else
  {
    prev_frame_pause_key = false;
  }

  if (!paused)
  {
    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Map>()->update();

    ECS::Components::PhysicsManager* pm = ECS::Components::Manager::get_instance().get_component<ECS::Components::PhysicsManager>();
    ECS::Components::PhysicsManager::Instance pmi = pm->get_instance(player);
    ECS::Components::DirectionManager* dm = ECS::Components::Manager::get_instance().get_component<ECS::Components::DirectionManager>();
    ECS::Components::DirectionManager::Instance dmi = dm->get_instance(player);
    ECS::Components::AnimationManager* am = ECS::Components::Manager::get_instance().get_component<ECS::Components::AnimationManager>();
    ECS::Components::AnimationManager::Instance ami = am->get_instance(player);
    ECS::Components::TransformManager* tm = ECS::Components::Manager::get_instance().get_component<ECS::Components::TransformManager>();
    ECS::Components::TransformManager::Instance tmi = tm->get_instance(player);
    
    if (in.attack && cooldown == 0)
    {
      attacking = true;
      cooldown = 30;
      /*
      ECS::Components::WeaponManager* wm = ECS::Components::Manager::get_instance().get_component<ECS::Components::WeaponManager>();
      ECS::Components::WeaponManager::Instance wmi;
      ECS::Systems::Weapon* ws = ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Weapon>();
      for (int i = 0; i < ws->weapons.size(); ++i)
      {
        ECS::Components::WeaponManager::Instance test;
        test = wm->get_instance(ws->weapons[i]);
        if (wm->get_id(test) == ECS::Systems::Inventory::slots[ECS::Systems::Inventory::slot_selected])
        {
          wmi = test;
          break;
        }
      }
      
      cooldown = wm->get_cooldown(wmi);

      // Create the projectile
      ECS::Entity projectile = ECS::EntityManager::get_instance().create_entity();
      ECS::Components::ProjectileManager* pm = ECS::Components::Manager::get_instance().get_component<ECS::Components::ProjectileManager>();
      ECS::Components::ProjectileDefManager* pdm = ECS::Components::Manager::get_instance().get_component<ECS::Components::ProjectileDefManager>();
      ECS::Components::ProjectileManager::Instance pmi = pm->add_component(projectile);
      
      // Set projectile
      // Get weapon info, get the projectile id (index)
      pm->set_projectile_def(pmi, pdm->data.entity[wm->get_projectile_id(wmi)]);

      pm->set_direction(pmi, dm->get_direction(dmi));
      pm->set_x(pmi, tm->get_x(tmi));
      pm->set_y(pmi, tm->get_y(tmi));
      pm->set_w(pmi, 64);
      pm->set_h(pmi, 64);
      pm->set_ticks(pmi, 0);
      ECS::Components::ProjectileDefManager::Instance pdmi = pdm->get_instance(pm->get_projectile_def(pmi));
      if (pdm->get_create(pdmi) != nullptr)
      {
        pdm->get_create(pdmi)(projectile);
      }
      */
    }

    if (in.slot_a)
      weapon = 0;
    if (in.slot_b)
      weapon = 1;
    if (in.slot_c)
      weapon = 2;
    if (in.slot_d)
      weapon = 3;

    // Figure out how to stop attacking when animation is done
    if (!attacking)
    {
      if (cooldown > 0)
        --cooldown;
    }

    if (in.up || in.right || in.down || in.left)
    {
      run_frames = 5;

      if (!attacking && am->get_state(ami) != weapon * 3 + 1)
      {
        am->set_state(ami, weapon * 3 + 1);
      }

      if (in.right || in.left)
      {
        if (in.right)
        {
          pm->set_x_accel(pmi, 2);
          dm->set_direction(player, 1);
        }
        else
        {
          pm->set_x_accel(pmi, -2);
          dm->set_direction(player, 3);
        }
      }
      else
      {
        pm->set_x_accel(pmi, pm->get_x_vel(pmi) / -2);
      }

      if (in.up || in.down)
      {
        if (in.up)
        {
          pm->set_y_accel(pmi, -2);
          dm->set_direction(player, 0);
        }
        else
        {
          pm->set_y_accel(pmi, 2);
          dm->set_direction(player, 2);
        }
      }
      else
      {
        pm->set_y_accel(pmi, pm->get_y_vel(pmi) / -2);
      }
    }
    else
    {
      if (--run_frames <= 0)
      {
        if (!attacking && am->get_state(ami) != weapon * 3)
        {
          am->set_state(ami, weapon * 3);
        }
      }

      pm->set_x_accel(pmi, pm->get_x_vel(pmi) / -2);
      pm->set_y_accel(pmi, pm->get_y_vel(pmi) / -2);
    }

    if (attacking)
    {
      if (am->get_state(ami) != weapon * 3 + 2)
      {
        am->set_state(ami, weapon * 3 + 2);
      }

      if (am->get_animation_pos(ami) == 0 && am->get_frames(ami) == 0)
      {
        ++attacking_i;
        if (attacking_i > 1)
        {
          attacking = false;
          attacking_i = 0;
        }
      }
    }

    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Physics>()->update();
    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Collision>()->update();

    // Move camera if player is at a certain 'box'
    int player_x = tm->get_x(tmi) - ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Camera>()->get_x();
    int player_y = tm->get_y(tmi) - ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Camera>()->get_y();

    if (player_x > 860)
    {
      camera_move_x = 960;
    }
    else if (player_x < 100)
    {
      camera_move_x = -960;
    }
    if (player_y > 540)
    {
      camera_move_y = 640;
    }
    else if (player_y < 100)
    {
      camera_move_y = -640;
    }

    ECS::Systems::Camera* cs = ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Camera>();
    if (camera_move_x != 0)
    {
      cs->move_camera(camera_move_x / 64, 0);
      camera_move_x -= camera_move_x / 64;
      if (std::abs(camera_move_x / 64) < 5)
        camera_move_x = 0;
    }
    if (camera_move_y != 0)
    {
      cs->move_camera(0, camera_move_y / 64);
      camera_move_y -= camera_move_y / 64;
      if (std::abs(camera_move_y / 64) < 5)
        camera_move_y = 0;
    }

    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Projectile>()->update();
    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Animation>()->update();
  }
  else
  {
    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Menu>()->update();
  }
}

void Game::Scenes::TestScene::draw(SDLW::Renderer* renderer)
{
  renderer->set_draw_color(0, 0, 0, 255);
  renderer->clear();
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Map>()->draw(renderer);
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Render>()->draw(renderer);
  if (paused)
    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Menu>()->draw(renderer);

  //ECS::Systems::Manager::get_instance().get_system<ECS::Systems::LineDebug>()->draw(renderer);
}
