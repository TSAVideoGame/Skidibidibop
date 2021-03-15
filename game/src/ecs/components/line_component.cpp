#include "line_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::LineManager> Game::ECS::Components::line_manager;

Game::ECS::Components::LineManager::LineManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity = reinterpret_cast<Entity*>(data.buffer);
  data.v1_x = reinterpret_cast<std::uint32_t*>(data.buffer);
  data.v1_y = reinterpret_cast<std::uint32_t*>(data.buffer);
  data.v2_x = reinterpret_cast<std::uint32_t*>(data.buffer);
  data.v2_y = reinterpret_cast<std::uint32_t*>(data.buffer);

  // Allocate at least the null component
  allocate(1);
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::LineManager::~LineManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::LineManager::Instance Game::ECS::Components::LineManager::get_instance(const Entity& e)
{
  Instance i;

  try
  {
    i = { map.at(e) };
  }
  catch (const std::out_of_range& ex)
  {
    i = { 0 };
  }

  return i;
}

/*
 * ========================================
 * Get / Set functions with instance handles
 * TODO: This visually looks messy
 * ========================================
 */
std::uint32_t Game::ECS::Components::LineManager::get_v1_x(Instance& i) { return data.v1_x[i.index]; }
void          Game::ECS::Components::LineManager::set_v1_x(Instance& i, std::uint32_t d) { data.v1_x[i.index] = d; }

std::uint32_t Game::ECS::Components::LineManager::get_v1_y(Instance& i) { return data.v1_y[i.index]; }
void          Game::ECS::Components::LineManager::set_v1_y(Instance& i, std::uint32_t d) { data.v1_y[i.index] = d; }

std::uint32_t Game::ECS::Components::LineManager::get_v2_x(Instance& i) { return data.v2_x[i.index]; }
void          Game::ECS::Components::LineManager::set_v2_x(Instance& i, std::uint32_t d) { data.v2_x[i.index] = d; }

std::uint32_t Game::ECS::Components::LineManager::get_v2_y(Instance& i) { return data.v2_y[i.index]; }
void          Game::ECS::Components::LineManager::set_v2_y(Instance& i, std::uint32_t d) { data.v2_y[i.index] = d; }

/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::LineManager::Instance Game::ECS::Components::LineManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({ e, data.instances });

  return { data.instances++ };
}

void Game::ECS::Components::LineManager::destroy_component(Instance& i)
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
  data.v1_x[i.index] = data.v1_x[last_index];
  data.v1_y[i.index] = data.v1_y[last_index];
  data.v2_x[i.index] = data.v2_x[last_index];
  data.v2_y[i.index] = data.v2_y[last_index];

  map[last_entity] = i.index;
  map.erase(delete_entity);

  --data.instances;
}

/*
 * ========================================
 * LineManager::allocate
 *
 * Reserves memory for transform components
 * Copies old buffer into new buffer
 * ========================================
 */
void Game::ECS::Components::LineManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (sizeof(Entity) + 4 * sizeof(std::uint32_t));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.v1_x = reinterpret_cast<std::uint32_t*>(new_data.entity + size);
  new_data.v1_y = new_data.v1_x + size;
  new_data.v2_x = new_data.v1_y + size;
  new_data.v2_y = new_data.v2_x + size;

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity, data.entity, data.instances * sizeof(Entity));
  std::memcpy(new_data.v1_x, data.v1_x, data.instances * sizeof(std::uint32_t));
  std::memcpy(new_data.v1_y, data.v1_y, data.instances * sizeof(std::uint32_t));
  std::memcpy(new_data.v2_x, data.v2_x, data.instances * sizeof(std::uint32_t));
  std::memcpy(new_data.v2_y, data.v2_y, data.instances * sizeof(std::uint32_t));

  std::free(data.buffer);

  data = new_data;
}
