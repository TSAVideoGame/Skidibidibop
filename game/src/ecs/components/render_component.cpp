#include "render_component.h"
#include <cstring>
#include <stdexcept>

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::RenderManager> Game::ECS::Components::render_manager;

Game::ECS::Components::RenderManager::RenderManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity    = reinterpret_cast<Entity*>(data.buffer);
  data.src_rect  = reinterpret_cast<SDL_Rect*>(data.buffer);
  data.dest_rect = reinterpret_cast<SDL_Rect*>(data.buffer);

  allocate(1); // allocate the null component
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::RenderManager::~RenderManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::RenderManager::Instance Game::ECS::Components::RenderManager::get_instance(const Entity& e)
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
 * ========================================
 */
SDL_Rect Game::ECS::Components::RenderManager::get_src_rect(Instance& i)              { return data.src_rect[i.index]; }
void     Game::ECS::Components::RenderManager::set_src_rect(Instance& i, SDL_Rect& r) { data.src_rect[i.index] = r; }

SDL_Rect Game::ECS::Components::RenderManager::get_dest_rect(Instance& i)              { return data.dest_rect[i.index]; }
void     Game::ECS::Components::RenderManager::set_dest_rect(Instance& i, SDL_Rect& r) { data.dest_rect[i.index] = r; }

/*
 * ========================================
 * Component Handling
 * ========================================
 */
Game::ECS::Components::RenderManager::Instance Game::ECS::Components::RenderManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({e, data.instances});

  return {data.instances++};
}

void Game::ECS::Components::RenderManager::destroy_component(Instance& i)
{
  if (i.index == 0)
    return;

  // To keep array tightl packed, swap last
  // element with the one to delete, and remove
  // the instance from the map
  
  std::size_t last_index = data.instances - 1;
  Entity delete_entity = data.entity[i.index];
  Entity last_entity = data.entity[last_index];

  data.entity[i.index] = data.entity[last_index];
  data.src_rect[i.index] = data.src_rect[last_index];
  data.dest_rect[i.index] = data.src_rect[last_index];

  map[last_entity] = i.index;
  map.erase(delete_entity);

  --data.instances;
}

/*
 * ========================================
 * RenderManager::allocate
 *
 * Reserves memory for render components
 * Copied old buffer into new buffer
 * ========================================
 */
void Game::ECS::Components::RenderManager::allocate(std::size_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  std::size_t bytes = size * (sizeof(Entity) + 2 * sizeof(SDL_Rect));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.src_rect = reinterpret_cast<SDL_Rect*>(new_data.entity + size);
  new_data.dest_rect = new_data.src_rect + size;

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity,    data.entity,    data.instances * sizeof(Entity));
  std::memcpy(new_data.src_rect,  data.src_rect,  data.instances * sizeof(SDL_Rect));
  std::memcpy(new_data.dest_rect, data.dest_rect, data.instances * sizeof(SDL_Rect));

  std::free(data.buffer);

  data = new_data;
}
