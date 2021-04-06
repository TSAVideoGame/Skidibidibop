#include "weapon_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

#include "core.h"

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::WeaponManager> Game::ECS::Components::weapon_manager;

Game::ECS::Components::WeaponManager::WeaponManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity = reinterpret_cast<Entity*>(data.buffer);
  data.id = reinterpret_cast<std::uint16_t*>(data.buffer);
  data.cooldown = reinterpret_cast<int*>(data.buffer);
  data.animation_id = reinterpret_cast<std::uint32_t*>(data.buffer);
  data.projectile_id = reinterpret_cast<std::uint32_t*>(data.buffer);

  // Allocate at least the null component
  allocate(1);
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::WeaponManager::~WeaponManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::WeaponManager::Instance Game::ECS::Components::WeaponManager::get_instance(const Entity& e)
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

Game::ECS::Components::WeaponManager::Instance Game::ECS::Components::WeaponManager::get_instance(std::uint16_t id)
{
  for (std::uint16_t i = 0; i < data.instances; ++i)
  {
    if (data.id[i] == id)
      return { i };
  }

  return { 0 };
}


/*
 * ========================================
 * Get / Set functions with instance handles
 * TODO: This visually looks messy
 * ========================================
 */
std::uint16_t Game::ECS::Components::WeaponManager::get_id(Instance& i) { return data.id[i.index]; }
void          Game::ECS::Components::WeaponManager::set_id(Instance& i, std::uint16_t x) { data.id[i.index] = x; }

int  Game::ECS::Components::WeaponManager::get_cooldown(Instance& i) { return data.cooldown[i.index]; }
void Game::ECS::Components::WeaponManager::set_cooldown(Instance& i, int x) { data.cooldown[i.index] = x; }

std::uint32_t Game::ECS::Components::WeaponManager::get_animation_id(Instance& i) { return data.animation_id[i.index]; }
void          Game::ECS::Components::WeaponManager::set_animation_id(Instance& i, std::uint32_t x) { data.animation_id[i.index] = x; }

std::uint32_t Game::ECS::Components::WeaponManager::get_projectile_id(Instance& i) { return data.projectile_id[i.index]; }
void          Game::ECS::Components::WeaponManager::set_projectile_id(Instance& i, std::uint32_t x) { data.projectile_id[i.index] = x; }

/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::WeaponManager::Instance Game::ECS::Components::WeaponManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({ e, data.instances });

  return { data.instances++ };
}

void Game::ECS::Components::WeaponManager::destroy_component(Instance& i)
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
  data.id[i.index] = data.id[last_index];
  data.cooldown[i.index] = data.cooldown[last_index];
  data.animation_id[i.index] = data.animation_id[last_index];
  data.projectile_id[i.index] = data.projectile_id[last_index];

  map[last_entity] = i.index;
  map.erase(delete_entity);

  --data.instances;
}

/*
 * ========================================
 * WeaponManager::allocate
 *
 * Reserves memory for transform components
 * Copies old buffer into new buffer
 * ========================================
 */
void Game::ECS::Components::WeaponManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (sizeof(Entity) + sizeof(std::uint16_t) + sizeof(int) + 2 * sizeof(std::uint32_t));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.id = reinterpret_cast<std::uint16_t*>(new_data.entity + size);
  new_data.cooldown = reinterpret_cast<int*>(new_data.id + size);
  new_data.animation_id = reinterpret_cast<std::uint32_t*>(new_data.cooldown + size);
  new_data.projectile_id = reinterpret_cast<std::uint32_t*>(new_data.animation_id + size);

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity, data.entity, data.instances * sizeof(Entity));
  std::memcpy(new_data.id, data.id, data.instances * sizeof(std::uint16_t));
  std::memcpy(new_data.cooldown, data.cooldown, data.instances * sizeof(int));
  std::memcpy(new_data.animation_id, data.animation_id, data.instances * sizeof(std::uint32_t));
  std::memcpy(new_data.projectile_id, data.projectile_id, data.instances * sizeof(std::uint32_t));

  std::free(data.buffer);

  data = new_data;
}
