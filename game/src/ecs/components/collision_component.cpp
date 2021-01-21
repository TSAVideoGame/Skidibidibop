#include "collision_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::CollisionManager> Game::ECS::Components::collision_manager;

Game::ECS::Components::CollisionManager::CollisionManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity   = reinterpret_cast<Entity*>(data.buffer);
  data.offset_x = reinterpret_cast<std::uint16_t*>(data.buffer);
  data.offset_y = reinterpret_cast<std::uint16_t*>(data.buffer);
  data.width    = reinterpret_cast<std::uint16_t*>(data.buffer);
  data.height   = reinterpret_cast<std::uint16_t*>(data.buffer);

  // Allocate at least the null component
  allocate(1);
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::CollisionManager::~CollisionManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::CollisionManager::Instance Game::ECS::Components::CollisionManager::get_instance(const Entity& e)
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
std::uint16_t Game::ECS::Components::CollisionManager::get_offset_x(Instance& i)                  { return data.offset_x[i.index]; }
void          Game::ECS::Components::CollisionManager::set_offset_x(Instance& i, std::uint16_t c) { data.offset_x[i.index] = c; }

std::uint16_t Game::ECS::Components::CollisionManager::get_offset_y(Instance& i)                  { return data.offset_y[i.index]; }
void          Game::ECS::Components::CollisionManager::set_offset_y(Instance& i, std::uint16_t c) { data.offset_y[i.index] = c; }

std::uint16_t Game::ECS::Components::CollisionManager::get_width(Instance& i)                  { return data.width[i.index]; }
void          Game::ECS::Components::CollisionManager::set_width(Instance& i, std::uint16_t c) { data.width[i.index] = c; }

std::uint16_t Game::ECS::Components::CollisionManager::get_height(Instance& i)                  { return data.height[i.index]; }
void          Game::ECS::Components::CollisionManager::set_height(Instance& i, std::uint16_t c) { data.height[i.index] = c; }

/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::CollisionManager::Instance Game::ECS::Components::CollisionManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({e, data.instances});

  return {data.instances++};
}

void Game::ECS::Components::CollisionManager::destroy_component(Instance& i)
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
  data.offset_x[i.index] = data.offset_x[last_index];
  data.offset_y[i.index] = data.offset_y[last_index];
  data.width[i.index] = data.width[last_index];
  data.height[i.index] = data.height[last_index];

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
void Game::ECS::Components::CollisionManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (sizeof(Entity) + 4 * sizeof(std::uint16_t));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity   = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.offset_x = reinterpret_cast<std::uint16_t*>(new_data.entity + size);
  new_data.offset_y = new_data.offset_x + size;
  new_data.width    = new_data.offset_y + size;
  new_data.height   = new_data.width + size;

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity,   data.entity,   data.instances * sizeof(Entity));
  std::memcpy(new_data.offset_x, data.offset_x, data.instances * sizeof(std::uint16_t));
  std::memcpy(new_data.offset_y, data.offset_y, data.instances * sizeof(std::uint16_t));
  std::memcpy(new_data.width,    data.width,    data.instances * sizeof(std::uint16_t));
  std::memcpy(new_data.height,   data.height,   data.instances * sizeof(std::uint16_t));

  std::free(data.buffer);

  data = new_data;
}
