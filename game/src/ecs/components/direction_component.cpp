#include "direction_component.h"
#include "render_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

#include "core.h"

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::DirectionManager> Game::ECS::Components::direction_manager;

Game::ECS::Components::DirectionManager::DirectionManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity = reinterpret_cast<Entity*>(data.buffer);
  data.direction = reinterpret_cast<std::int8_t*>(data.buffer);

  // Allocate at least the null component
  allocate(1);
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::DirectionManager::~DirectionManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::DirectionManager::Instance Game::ECS::Components::DirectionManager::get_instance(const Entity& e)
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
std::int8_t Game::ECS::Components::DirectionManager::get_direction(Instance& i) { return data.direction[i.index]; }
void        Game::ECS::Components::DirectionManager::set_direction(Entity& e, std::int8_t x)
{
  Instance i = get_instance(e);

  // Change dest rect
  RenderManager* rm = Manager::get_instance().get_component<RenderManager>();
  RenderManager::Instance rmi = rm->get_instance(e);
  SDL_Rect new_rect = rm->get_src_rect(rmi);
  new_rect.y += (x - get_direction(i)) * 32;
  rm->set_src_rect(rmi, new_rect);

  // Actually change direction
  data.direction[i.index] = x;
}


/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::DirectionManager::Instance Game::ECS::Components::DirectionManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({ e, data.instances });

  data.direction[data.instances] = 0;

  return { data.instances++ };
}

void Game::ECS::Components::DirectionManager::destroy_component(Instance& i)
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
  data.direction[i.index] = data.direction[last_index];

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
void Game::ECS::Components::DirectionManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (sizeof(Entity) + sizeof(std::int8_t));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.direction = reinterpret_cast<std::int8_t*>(new_data.entity + size);

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity,    data.entity,    data.instances * sizeof(Entity));
  std::memcpy(new_data.direction, data.direction, data.instances * sizeof(std::int8_t));

  std::free(data.buffer);

  data = new_data;
}
