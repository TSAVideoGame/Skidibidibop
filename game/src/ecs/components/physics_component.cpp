#include "physics_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::PhysicsManager> Game::ECS::Components::physics_manager;

Game::ECS::Components::PhysicsManager::PhysicsManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity    = reinterpret_cast<Entity*>(data.buffer);
  data.x_vel     = reinterpret_cast<float*>(data.buffer);
  data.y_vel     = reinterpret_cast<float*>(data.buffer);
  data.x_accel   = reinterpret_cast<float*>(data.buffer);
  data.y_accel   = reinterpret_cast<float*>(data.buffer);
  data.max_x_vel = reinterpret_cast<float*>(data.buffer);
  data.max_y_vel = reinterpret_cast<float*>(data.buffer);

  // Allocate at least the null component
  allocate(1);
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::PhysicsManager::~PhysicsManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::PhysicsManager::Instance Game::ECS::Components::PhysicsManager::get_instance(const Entity& e)
{
  Instance i;

  try 
  {
    i = {map.at(e)};
  }
  catch (const std::out_of_range& ex)
  {
    i = {0};
  }

  return i;
}

/*
 * ========================================
 * Get / Set functions with instance handles
 * TODO: This visually looks messy
 * ========================================
 */
float Game::ECS::Components::PhysicsManager::get_x_vel(Instance& i)            { return data.x_vel[i.index]; }
void  Game::ECS::Components::PhysicsManager::set_x_vel(Instance& i, float vel) { data.x_vel[i.index] = vel; }

float Game::ECS::Components::PhysicsManager::get_y_vel(Instance& i)            { return data.y_vel[i.index]; }
void  Game::ECS::Components::PhysicsManager::set_y_vel(Instance& i, float vel) { data.y_vel[i.index] = vel; }

float Game::ECS::Components::PhysicsManager::get_x_accel(Instance& i)              { return data.x_accel[i.index]; }
void  Game::ECS::Components::PhysicsManager::set_x_accel(Instance& i, float accel) { data.x_accel[i.index] = accel; }

float Game::ECS::Components::PhysicsManager::get_y_accel(Instance& i)              { return data.y_accel[i.index]; }
void  Game::ECS::Components::PhysicsManager::set_y_accel(Instance& i, float accel) { data.y_accel[i.index] = accel; }

float Game::ECS::Components::PhysicsManager::get_max_x_vel(Instance& i)            { return data.max_x_vel[i.index]; }
void  Game::ECS::Components::PhysicsManager::set_max_x_vel(Instance& i, float vel) { data.max_x_vel[i.index] = vel; }

float Game::ECS::Components::PhysicsManager::get_max_y_vel(Instance& i)            { return data.max_y_vel[i.index]; }
void  Game::ECS::Components::PhysicsManager::set_max_y_vel(Instance& i, float vel) { data.max_y_vel[i.index] = vel; }

/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::PhysicsManager::Instance Game::ECS::Components::PhysicsManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({e, data.instances});

  return {data.instances++};
}

void Game::ECS::Components::PhysicsManager::destroy_component(Instance& i)
{
  if (i.index == 0)
    return;

  // To keep array tightly packed, swap last
  // element with the one to delete, and remove
  // the instance from the map
  std::size_t last_index = data.instances - 1;
  Entity delete_entity = data.entity[i.index];
  Entity last_entity = data.entity[last_index];

  data.entity[i.index] = data.entity[last_index];
  data.x_vel[i.index] = data.x_vel[last_index];
  data.y_vel[i.index] = data.y_vel[last_index];
  data.x_accel[i.index] = data.x_accel[last_index];
  data.y_accel[i.index] = data.y_accel[last_index];
  data.max_x_vel[i.index] = data.max_x_vel[last_index];
  data.max_y_vel[i.index] = data.max_y_vel[last_index];

  map[last_entity] = i.index;
  map.erase(delete_entity);

  --data.instances;
}

/*
 * ========================================
 * TransformManager::allocate
 *
 * Reserves memory for transform components
 * Copies old buffer into new buffer
 * ========================================
 */
void Game::ECS::Components::PhysicsManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (sizeof(Entity) + 6 * sizeof(float));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.x_vel = reinterpret_cast<float*>(new_data.entity + size);
  new_data.y_vel = new_data.x_vel + size;
  new_data.x_accel = new_data.y_vel + size;
  new_data.y_accel = new_data.x_accel + size;
  new_data.max_x_vel = new_data.y_accel + size;
  new_data.max_y_vel = new_data.max_x_vel + size;

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity,    data.entity,     data.instances * sizeof(Entity));
  std::memcpy(new_data.x_vel,     data.x_vel,      data.instances * sizeof(float));
  std::memcpy(new_data.y_vel,     data.y_vel,      data.instances * sizeof(float));
  std::memcpy(new_data.x_accel,   data.x_accel,    data.instances * sizeof(float));
  std::memcpy(new_data.y_accel,   data.y_accel,    data.instances * sizeof(float));
  std::memcpy(new_data.max_x_vel, data.max_x_vel,  data.instances * sizeof(float));
  std::memcpy(new_data.max_y_vel, data.max_y_vel,  data.instances * sizeof(float));

  std::free(data.buffer);

  data = new_data;
}
