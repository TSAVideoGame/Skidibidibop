#include "camera_system.h"
#include "component.h"
#include <stdexcept>
#include "core.h"

// Register
Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Camera> camera_system;

// Static variables
Game::ECS::Entity Game::ECS::Systems::Camera::cameras[10];
std::uint32_t Game::ECS::Systems::Camera::active_camera = 0;

// Creates a default camera
void Game::ECS::Systems::Camera::init()
{
  cameras[0] = EntityManager::get_instance().create_entity();
  Components::CameraManager* cm = Components::Manager::get_instance().get_component<Components::CameraManager>();
  Components::CameraManager::Instance cmi = cm->add_component(cameras[0]);
  cm->set_chunk(cmi, 0);
  cm->set_x(cmi, 0);
  cm->set_y(cmi, 0);
}

void Game::ECS::Systems::Camera::set_active_camera(std::uint32_t index)
{

}

Game::ECS::Components::CameraManager::Instance Game::ECS::Systems::Camera::get_active_camera()
{
  return Components::Manager::get_instance().get_component<Components::CameraManager>()->get_instance(cameras[active_camera]);
}

/*
 * ========================================
 * move_camera
 *
 * Moves camera
 * TODO: Bounds checking
 * ========================================
 */
void Game::ECS::Systems::Camera::move_camera(int x, int y)
{
  Components::CameraManager* cm = Components::Manager::get_instance().get_component<Components::CameraManager>();
  Components::CameraManager::Instance cmi = cm->get_instance(cameras[active_camera]);
  // X
  cm->set_x(cmi, cm->get_x(cmi) + x);
  /*if (cm->get_x(cmi) >= 800)
  {
    cm->set_x(cmi, cm->get_x(cmi) - 800);
    cm->set_chunk(cmi, cm->get_chunk(cmi) + 1);
  }
  else if (cm->get_x(cmi) < 0)
  {
    cm->set_x(cmi, cm->get_x(cmi) + 800);
    cm->set_chunk(cmi, cm->get_chunk(cmi) - 1);
  }*/
  // Y
  cm->set_y(cmi, cm->get_y(cmi) + y);
  /*if (cm->get_y(cmi) >= 800)
  {
    cm->set_y(cmi, cm->get_y(cmi) - 800);
    cm->set_chunk(cmi, cm->get_chunk(cmi) + Core::map_helper.x);
  }
  else if (cm->get_y(cmi) < 0)
  {
    cm->set_y(cmi, cm->get_y(cmi) + 800);
    cm->set_chunk(cmi, cm->get_chunk(cmi) - Core::map_helper.x);
  }*/
}

std::uint32_t Game::ECS::Systems::Camera::get_x()
{
  Components::CameraManager* cm = Components::Manager::get_instance().get_component<Components::CameraManager>();
  Components::CameraManager::Instance cmi = cm->get_instance(cameras[active_camera]);

  return cm->get_x(cmi); 
}

std::uint32_t Game::ECS::Systems::Camera::get_y()
{
  Components::CameraManager* cm = Components::Manager::get_instance().get_component<Components::CameraManager>();
  Components::CameraManager::Instance cmi = cm->get_instance(cameras[active_camera]);

  return cm->get_y(cmi); 
}
