#include "projectile_component.h"
#include "render_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

#include "core.h"

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::ProjectileManager> Game::ECS::Components::projectile_manager;

Game::ECS::Components::ProjectileManager::ProjectileManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity = reinterpret_cast<Entity*>(data.buffer);
  data.x = reinterpret_cast<int*>(data.buffer);
  data.y = reinterpret_cast<int*>(data.buffer);
  data.w = reinterpret_cast<int*>(data.buffer);
  data.h = reinterpret_cast<int*>(data.buffer);
  data.direction = reinterpret_cast<int*>(data.buffer);
  data.ticks = reinterpret_cast<int*>(data.buffer);
  data.projectile_def = reinterpret_cast<Entity*>(data.buffer);

  // Allocate at least the null component
  allocate(1);
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::ProjectileManager::~ProjectileManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::ProjectileManager::Instance Game::ECS::Components::ProjectileManager::get_instance(const Entity& e)
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
int  Game::ECS::Components::ProjectileManager::get_x(Instance& i) { return data.x[i.index]; }
void Game::ECS::Components::ProjectileManager::set_x(Instance& i, int x) { data.x[i.index] = x; }

int  Game::ECS::Components::ProjectileManager::get_y(Instance& i) { return data.y[i.index]; }
void Game::ECS::Components::ProjectileManager::set_y(Instance& i, int x) { data.y[i.index] = x; }

int  Game::ECS::Components::ProjectileManager::get_w(Instance& i) { return data.w[i.index]; }
void Game::ECS::Components::ProjectileManager::set_w(Instance& i, int x) { data.w[i.index] = x; }

int  Game::ECS::Components::ProjectileManager::get_h(Instance& i) { return data.h[i.index]; }
void Game::ECS::Components::ProjectileManager::set_h(Instance& i, int x) { data.h[i.index] = x; }

int  Game::ECS::Components::ProjectileManager::get_direction(Instance& i) { return data.direction[i.index]; }
void Game::ECS::Components::ProjectileManager::set_direction(Instance& i, int x) { data.direction[i.index] = x; }

int  Game::ECS::Components::ProjectileManager::get_ticks(Instance& i) { return data.ticks[i.index]; }
void Game::ECS::Components::ProjectileManager::set_ticks(Instance& i, int x) { data.ticks[i.index] = x; }

Game::ECS::Entity Game::ECS::Components::ProjectileManager::get_projectile_def(Instance& i) { return data.projectile_def[i.index]; }
void              Game::ECS::Components::ProjectileManager::set_projectile_def(Instance& i, Entity x) { data.projectile_def[i.index] = x; }

/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::ProjectileManager::Instance Game::ECS::Components::ProjectileManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({ e, data.instances });

  return { data.instances++ };
}

void Game::ECS::Components::ProjectileManager::destroy_component(Instance& i)
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
  data.x[i.index] = data.x[last_index];
  data.y[i.index] = data.y[last_index];
  data.w[i.index] = data.w[last_index];
  data.h[i.index] = data.h[last_index];
  data.direction[i.index] = data.direction[last_index];
  data.ticks[i.index] = data.ticks[last_index];
  data.projectile_def[i.index] = data.projectile_def[last_index];

  map[last_entity] = i.index;
  map.erase(delete_entity);

  --data.instances;
}

/*
 * ========================================
 * ProjectileManager::allocate
 *
 * Reserves memory for transform components
 * Copies old buffer into new buffer
 * ========================================
 */
void Game::ECS::Components::ProjectileManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (2 * sizeof(Entity) + 6 * sizeof(int));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.x = reinterpret_cast<int*>(new_data.entity + size);
  new_data.y = reinterpret_cast<int*>(new_data.x + size);
  new_data.w = reinterpret_cast<int*>(new_data.y + size);
  new_data.h = reinterpret_cast<int*>(new_data.w + size);
  new_data.direction = reinterpret_cast<int*>(new_data.h + size);
  new_data.ticks = reinterpret_cast<int*>(new_data.direction + size);
  new_data.projectile_def = reinterpret_cast<Entity*>(new_data.ticks + size);

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity,    data.entity,    data.instances * sizeof(Entity));
  std::memcpy(new_data.x,         data.x,         data.instances * sizeof(int));
  std::memcpy(new_data.y,         data.y,         data.instances * sizeof(int));
  std::memcpy(new_data.w,         data.w,         data.instances * sizeof(int));
  std::memcpy(new_data.h,         data.h,         data.instances * sizeof(int));
  std::memcpy(new_data.direction, data.direction, data.instances * sizeof(int));
  std::memcpy(new_data.ticks,     data.ticks,     data.instances * sizeof(int));
  std::memcpy(new_data.entity,    data.entity,    data.instances * sizeof(Entity));

  std::free(data.buffer);

  data = new_data;
}
