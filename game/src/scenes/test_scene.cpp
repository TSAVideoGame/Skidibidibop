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
  
  ECS::Components::RenderManager::Instance rmi = rm->add_component(player);

  SDL_Rect src_rect = {0, 1 * 32, 32, 32};
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
  player_run.animation_data.push_back({4, 4});
  player_run.animation_data.push_back({5, 4});
  player_run.animation_data.push_back({6, 4});
  player_run.animation_data.push_back({7, 4});
  player_run.animation_data.push_back({8, 4});
  player_run.animation_data.push_back({9, 4});

  player_animations.push_back(player_idle);
  player_animations.push_back(player_run);

  am->set_animations(ami, player_animations);
}

Game::Scenes::TestScene::~TestScene()
{
  
}

static int camera_move_x = 0;
static int camera_move_y = 0;
static int run_frames = 0; // Don't immediately return to idle animation
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
    ECS::Components::AnimationManager* am = ECS::Components::Manager::get_instance().get_component<ECS::Components::AnimationManager>();
    ECS::Components::AnimationManager::Instance ami = am->get_instance(player);
    
    if (in.up || in.right || in.down || in.left)
    {
      run_frames = 5;

      if (am->get_state(ami) != 1)
      {
        am->set_state(ami, 1);
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
        if (am->get_state(ami) != 0)
        {
          am->set_state(ami, 0);
        }
      }

      pm->set_x_accel(pmi, pm->get_x_vel(pmi) / -2);
      pm->set_y_accel(pmi, pm->get_y_vel(pmi) / -2);
    }

    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Physics>()->update();
    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Collision>()->update();

    // Move camera if player is at a certain 'box'
    ECS::Components::TransformManager* tm = ECS::Components::Manager::get_instance().get_component<ECS::Components::TransformManager>();
    ECS::Components::TransformManager::Instance tmi = tm->get_instance(player);
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
