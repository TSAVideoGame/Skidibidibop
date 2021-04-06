#include "projectile_def_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::ProjectileDefManager> Game::ECS::Components::projectile_def_manager;

Game::ECS::Components::ProjectileDefManager::ProjectileDefManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity = reinterpret_cast<Entity*>(data.buffer);
  data.damage = reinterpret_cast<int*>(data.buffer);
  data.status = reinterpret_cast<int*>(data.buffer);
  data.bounce = reinterpret_cast<float*>(data.buffer);
  data.on_create = reinterpret_cast<projectile_create_function*>(data.buffer);
  data.on_update = reinterpret_cast<projectile_update_function*>(data.buffer);
  data.on_destroy = reinterpret_cast<projectile_function*>(data.buffer);
  data.max_ticks = reinterpret_cast<int*>(data.buffer);
  data.flag = reinterpret_cast<int*>(data.buffer);

  // Allocate at least the null component
  allocate(1);
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::ProjectileDefManager::~ProjectileDefManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::ProjectileDefManager::Instance Game::ECS::Components::ProjectileDefManager::get_instance(const Entity& e)
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
int  Game::ECS::Components::ProjectileDefManager::get_damage(Instance& i) { return data.damage[i.index]; }
void Game::ECS::Components::ProjectileDefManager::set_damage(Instance& i, int x) { data.damage[i.index] = x; }

int  Game::ECS::Components::ProjectileDefManager::get_status(Instance& i) { return data.status[i.index]; }
void Game::ECS::Components::ProjectileDefManager::set_status(Instance& i, int x) { data.status[i.index] = x; }

float Game::ECS::Components::ProjectileDefManager::get_bounce(Instance& i) { return data.bounce[i.index]; }
void  Game::ECS::Components::ProjectileDefManager::set_bounce(Instance& i, float x) { data.bounce[i.index] = x; }

Game::ECS::Components::ProjectileDefManager::projectile_create_function Game::ECS::Components::ProjectileDefManager::get_create(Instance& i) { return data.on_create[i.index]; }
void Game::ECS::Components::ProjectileDefManager::set_create(Instance& i, projectile_create_function x) { data.on_create[i.index] = x; }

Game::ECS::Components::ProjectileDefManager::projectile_update_function Game::ECS::Components::ProjectileDefManager::get_update(Instance& i) { return data.on_update[i.index]; }
void Game::ECS::Components::ProjectileDefManager::set_update(Instance& i, projectile_update_function x) { data.on_update[i.index] = x; }

Game::ECS::Components::ProjectileDefManager::projectile_function Game::ECS::Components::ProjectileDefManager::get_destroy(Instance& i) { return data.on_destroy[i.index]; }
void Game::ECS::Components::ProjectileDefManager::set_destroy(Instance& i, projectile_function x) { data.on_destroy[i.index] = x; }

int  Game::ECS::Components::ProjectileDefManager::get_max_ticks(Instance& i) { return data.max_ticks[i.index]; }
void Game::ECS::Components::ProjectileDefManager::set_max_ticks(Instance& i, int x) { data.max_ticks[i.index] = x; }

int  Game::ECS::Components::ProjectileDefManager::get_flag(Instance& i) { return data.flag[i.index]; }
void Game::ECS::Components::ProjectileDefManager::set_flag(Instance& i, int x) { data.flag[i.index] = x; }

/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::ProjectileDefManager::Instance Game::ECS::Components::ProjectileDefManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({ e, data.instances });

  return { data.instances++ };
}

void Game::ECS::Components::ProjectileDefManager::destroy_component(Instance& i)
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
  data.damage[i.index] = data.damage[last_index];
  data.status[i.index] = data.status[last_index];
  data.bounce[i.index] = data.bounce[last_index];
  data.on_create[i.index] = data.on_create[last_index];
  data.on_update[i.index] = data.on_update[last_index];
  data.on_destroy[i.index] = data.on_destroy[last_index];
  data.max_ticks[i.index] = data.max_ticks[last_index];
  data.flag[i.index] = data.flag[last_index];

  map[last_entity] = i.index;
  map.erase(delete_entity);

  --data.instances;
}

/*
 * ========================================
 * DirectionManager::allocate
 *
 * Reserves memory for transform components
 * Copies old buffer into new buffer
 * ========================================
 */
void Game::ECS::Components::ProjectileDefManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (sizeof(Entity) + 4 * sizeof(int) + sizeof(float) + sizeof(projectile_create_function) + sizeof(projectile_update_function) + sizeof(projectile_function));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.damage = reinterpret_cast<int*>(new_data.entity + size);
  new_data.status = reinterpret_cast<int*>(new_data.damage + size);
  new_data.bounce = reinterpret_cast<float*>(new_data.status + size);
  new_data.on_create = reinterpret_cast<projectile_create_function*>(new_data.bounce + size);
  new_data.on_update = reinterpret_cast<projectile_update_function*>(new_data.on_create + size);
  new_data.on_destroy = reinterpret_cast<projectile_function*>(new_data.on_update + size);
  new_data.max_ticks = reinterpret_cast<int*>(new_data.on_destroy + size);
  new_data.flag = reinterpret_cast<int*>(new_data.max_ticks + size);

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity, data.entity, data.instances * sizeof(Entity));
  std::memcpy(new_data.damage, data.damage, data.instances * sizeof(int));
  std::memcpy(new_data.status, data.status, data.instances * sizeof(int));
  std::memcpy(new_data.bounce, data.bounce, data.instances * sizeof(float));
  std::memcpy(new_data.on_create, data.on_create, data.instances * sizeof(projectile_create_function));
  std::memcpy(new_data.on_update, data.on_update, data.instances * sizeof(projectile_update_function));
  std::memcpy(new_data.on_destroy, data.on_destroy, data.instances * sizeof(projectile_function));
  std::memcpy(new_data.max_ticks, data.max_ticks, data.instances * sizeof(int));
  std::memcpy(new_data.flag, data.flag, data.instances * sizeof(int));

  std::free(data.buffer);

  data = new_data;
}
