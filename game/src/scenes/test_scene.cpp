#include "test_scene.h"
#include "entity.h"
#include "transform_component.h"
#include "render_component.h"
#include "render_system.h"
#include "physics_component.h"
#include "physics_system.h"
#include "map_system.h"
#include "camera_system.h"
#include "core.h"
#include "constants.h"

static Game::ECS::Entity player = Game::ECS::EntityManager::get_instance().get_null();

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

  tm->set_offset_x(tmi, Constants.Window.width / 2);
  tm->set_offset_y(tmi, Constants.Window.height / 2);
  
  ECS::Components::RenderManager::Instance rmi = rm->add_component(player);

  SDL_Rect src_rect = {0, 6 * 32, 32, 32};
  rm->set_src_rect(rmi, src_rect);
  SDL_Rect dest_rect = {0, 0, 32, 32};
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
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Map>()->update();

  ECS::Components::PhysicsManager* pm = ECS::Components::Manager::get_instance().get_component<ECS::Components::PhysicsManager>();
  ECS::Components::PhysicsManager::Instance pmi = pm->get_instance(player);
  
  Input::Data in = Core::get_inputs();

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

  if (tm->get_offset_x(tmi) > 760)
  {
    camera_move_x = 800;
  }
  else if (tm->get_offset_x(tmi) < 40)
  {
    camera_move_x = -800;
  }
  if (tm->get_offset_y(tmi) > 760)
  {
    camera_move_y = 800;
  }
  else if (tm->get_offset_y(tmi) < 40)
  {
    camera_move_y = -800;
  }

  ECS::Systems::Camera* cs = ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Camera>();
  if (camera_move_x != 0)
  {
    camera_move_x /= 8;
    cs->move_camera(camera_move_x, 0);
  }
  if (camera_move_y != 0)
  {
    camera_move_y /= 8;
    cs->move_camera(0, camera_move_y);
  }
}

void Game::Scenes::TestScene::draw(SDLW::Renderer* renderer)
{
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Map>()->draw(renderer);
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Render>()->draw(renderer); 
}
