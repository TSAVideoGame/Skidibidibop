#include "transform_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::TransformManager> Game::ECS::Components::transform_manager;

Game::ECS::Components::TransformManager::TransformManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity = reinterpret_cast<Entity*>(data.buffer);
  data.tile_x = reinterpret_cast<std::uint16_t*>(data.buffer);
  data.tile_y = reinterpret_cast<std::uint16_t*>(data.buffer);
  data.offset_x = reinterpret_cast<int*>(data.buffer);
  data.offset_y = reinterpret_cast<int*>(data.buffer);

  // Allocate at least the null component
  allocate(1);
}

Game::ECS::Components::TransformManager::~TransformManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::TransformManager::Instance Game::ECS::Components::TransformManager::get_instance(Entity& e)
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
std::uint16_t Game::ECS::Components::TransformManager::get_tile_x(Instance& i)                  { return data.tile_x[i.index]; }
void          Game::ECS::Components::TransformManager::set_tile_x(Instance& i, std::uint16_t x) { data.tile_x[i.index] = x; }

std::uint16_t Game::ECS::Components::TransformManager::get_tile_y(Instance& i)                  { return data.tile_y[i.index]; }
void          Game::ECS::Components::TransformManager::set_tile_y(Instance& i, std::uint16_t y) { data.tile_y[i.index] = y; }

int  Game::ECS::Components::TransformManager::get_offset_x(Instance& i)        { return data.offset_x[i.index]; }
void Game::ECS::Components::TransformManager::set_offset_x(Instance& i, int x) { data.offset_x[i.index] = x; }

int  Game::ECS::Components::TransformManager::get_offset_y(Instance& i)        { return data.offset_y[i.index]; }
void Game::ECS::Components::TransformManager::set_offset_y(Instance& i, int y) { data.offset_y[i.index] = y; }

/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::TransformManager::Instance Game::ECS::Components::TransformManager::add_component(Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(++data.instances);

  data.entity[data.instances - 1] = e;

  map.insert({e, data.instances - 1});

  return {data.instances - 1};
}

void Game::ECS::Components::TransformManager::destroy_component(Instance& i)
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
  data.tile_x[i.index] = data.tile_x[last_index];
  data.tile_y[i.index] = data.tile_y[last_index];
  data.offset_x[i.index] = data.offset_x[last_index];
  data.offset_y[i.index] = data.offset_y[last_index];

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
void Game::ECS::Components::TransformManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (sizeof(Entity) + 2 * sizeof(std::uint16_t) + 2 * sizeof(int));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.tile_x = reinterpret_cast<std::uint16_t*>(new_data.entity + size);
  new_data.tile_y = new_data.tile_x + size;
  new_data.offset_x = reinterpret_cast<int*>(new_data.tile_y + size);
  new_data.offset_y = new_data.offset_x + size;

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity,   data.entity,   data.instances * sizeof(Entity));
  std::memcpy(new_data.tile_x,   data.tile_x,   data.instances * sizeof(std::uint16_t));
  std::memcpy(new_data.tile_y,   data.tile_y,   data.instances * sizeof(std::uint16_t));
  std::memcpy(new_data.offset_x, data.offset_x, data.instances * sizeof(int));
  std::memcpy(new_data.offset_y, data.offset_y, data.instances * sizeof(int));

  std::free(data.buffer);

  data = new_data;
}
