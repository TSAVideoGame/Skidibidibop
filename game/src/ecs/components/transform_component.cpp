#include "transform_component.h"
#include <cstdlib>
#include <cstring>

Game::ECS::Components::TransformManager::TransformManager()
{

}

Game::ECS::Components::TransformManager::~TransformManager()
{
  free(data.buffer);
}

Game::ECS::Components::TransformManager::Instance Game::ECS::Components::TransformManager::get_instance(Entity& e)
{
  return {map.at(e)};
}

/*
 * ========================================
 * Get functions with instance handles
 * ========================================
 */
std::uint16_t Game::ECS::Components::TransformManager::get_tile_x(Instance& i)
{
  return data.tile_x[i.index];
}

std::uint16_t Game::ECS::Components::TransformManager::get_tile_y(Instance& i)
{
  return data.tile_y[i.index];
}

int Game::ECS::Components::TransformManager::get_offset_x(Instance& i)
{
  return data.offset_x[i.index];
}

int Game::ECS::Components::TransformManager::get_offset_y(Instance& i)
{
  return data.offset_y[i.index];
}

/*
 * ========================================
 * TODO
 * Component handling
 * ========================================
 */
Game::ECS::Components::TransformManager::Instance Game::ECS::Components::TransformManager::add_component(Entity&)
{

}

void Game::ECS::Components::TransformManager::destroy_component(Instance&)
{

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

  free(data.buffer);

  data = new_data;
}
