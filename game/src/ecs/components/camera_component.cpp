#include "camera_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::CameraManager> Game::ECS::Components::camera_manager;

Game::ECS::Components::CameraManager::CameraManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity = reinterpret_cast<Entity*>(data.buffer);
  data.chunk  = reinterpret_cast<std::uint32_t*>(data.buffer);
  data.x      = reinterpret_cast<int*>(data.buffer);
  data.y      = reinterpret_cast<int*>(data.buffer);

  // Allocate at least the null component
  allocate(1);
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::CameraManager::~CameraManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::CameraManager::Instance Game::ECS::Components::CameraManager::get_instance(const Entity& e)
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
std::uint32_t Game::ECS::Components::CameraManager::get_chunk(Instance& i)                    { return data.chunk[i.index]; }
void          Game::ECS::Components::CameraManager::set_chunk(Instance& i, std::uint32_t c)   { data.chunk[i.index] = c; }

int   Game::ECS::Components::CameraManager::get_x(Instance& i)         { return data.x[i.index]; }
void  Game::ECS::Components::CameraManager::set_x(Instance& i, int x)  { data.x[i.index] = x; }

int   Game::ECS::Components::CameraManager::get_y(Instance& i)         { return data.y[i.index]; }
void  Game::ECS::Components::CameraManager::set_y(Instance& i, int y)  { data.y[i.index] = y; }

/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::CameraManager::Instance Game::ECS::Components::CameraManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({e, data.instances});

  return {data.instances++};
}

void Game::ECS::Components::CameraManager::destroy_component(Instance& i)
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
  data.chunk[i.index] = data.chunk[last_index];
  data.x[i.index] = data.x[last_index];
  data.y[i.index] = data.y[last_index];

  map[last_entity] = i.index;
  map.erase(delete_entity);

  --data.instances;
}

/*
 * ========================================
 * CameraManager::allocate
 *
 * Reserves memory for transform components
 * Copies old buffer into new buffer
 * ========================================
 */
void Game::ECS::Components::CameraManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (sizeof(Entity) + sizeof(std::uint32_t) + 2 * sizeof(int));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.chunk = reinterpret_cast<std::uint32_t*>(new_data.entity + size);
  new_data.x = reinterpret_cast<int*>(new_data.chunk + size);
  new_data.y = new_data.x + size;

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity,    data.entity,     data.instances * sizeof(Entity));
  std::memcpy(new_data.chunk,     data.chunk,      data.instances * sizeof(std::uint32_t));
  std::memcpy(new_data.x,         data.x,          data.instances * sizeof(int));
  std::memcpy(new_data.y,         data.y,          data.instances * sizeof(int));

  std::free(data.buffer);

  data = new_data;
}
