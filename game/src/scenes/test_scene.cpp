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

  // Set up the player
  player = Game::ECS::EntityManager::get_instance().create_entity();

  ECS::Components::TransformManager::Instance tmi = tm->add_component(player);

  tm->set_x(tmi, Constants.Window.width / 2);
  tm->set_y(tmi, Constants.Window.height / 2);
  
  ECS::Components::RenderManager::Instance rmi = rm->add_component(player);

  SDL_Rect src_rect = {0, 6 * 32, 32, 32};
  rm->set_src_rect(rmi, src_rect);
  SDL_Rect dest_rect = {0, 0, 64, 64};
  rm->set_dest_rect(rmi, dest_rect);

  ECS::Components::PhysicsManager::Instance pmi = pm->add_component(player);

  pm->set_x_vel(pmi, 0);
  pm->set_y_vel(pmi, 0);
  pm->set_x_accel(pmi, 0);
  pm->set_y_accel(pmi, 0);
  pm->set_max_x_vel(pmi, 11);
  pm->set_max_y_vel(pmi, 11);
}

Game::Scenes::TestScene::~TestScene()
{
  
}

static int camera_move_x = 0;
static int camera_move_y = 0;
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
    
    if (in.up || in.down)
    {
      if (in.up)
        pm->set_y_accel(pmi, -2);
      else
        pm->set_y_accel(pmi, 2);
    }
    else
    {
      pm->set_y_accel(pmi, pm->get_y_vel(pmi) / -2);
    }

    if (in.right || in.left)
    {
      if (in.right)
        pm->set_x_accel(pmi, 2);
      else
        pm->set_x_accel(pmi, -2);
    }
    else
    {
      pm->set_x_accel(pmi, pm->get_x_vel(pmi) / -2);
    }

    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Physics>()->update();

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
  }
  else
  {
    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Menu>()->update();
  }
}

void Game::Scenes::TestScene::draw(SDLW::Renderer* renderer)
{
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Map>()->draw(renderer);
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Render>()->draw(renderer);
  if (paused)
    ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Menu>()->draw(renderer);
}
