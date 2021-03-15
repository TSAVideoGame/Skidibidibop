#include "animation_component.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

Game::ECS::Components::Manager::RegisterComponent<Game::ECS::Components::AnimationManager> Game::ECS::Components::animation_manager;

Game::ECS::Components::AnimationManager::AnimationManager()
{
  // Initialze data
  data.instances = 0;
  data.allocated = 0;
  data.buffer = std::malloc(0);

  data.entity         = reinterpret_cast<Entity*>(data.buffer);
  data.state          = reinterpret_cast<std::uint8_t*>(data.buffer);
  data.frames         = reinterpret_cast<std::uint8_t*>(data.buffer);
  data.animation_pos  = reinterpret_cast<std::uint8_t*>(data.buffer);

  data.animations = new std::vector<Animation>[0];


  // Allocate at least the null component
  allocate(1);
  add_component(EntityManager::get_instance().get_null());
}

Game::ECS::Components::AnimationManager::~AnimationManager()
{
  std::free(data.buffer);
}

Game::ECS::Components::AnimationManager::Instance Game::ECS::Components::AnimationManager::get_instance(const Entity& e)
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
std::uint8_t                                                    Game::ECS::Components::AnimationManager::get_state(Instance& i) { return data.state[i.index]; }
void                                                            Game::ECS::Components::AnimationManager::set_state(Instance& i, std::uint8_t x) { data.state[i.index] = x; data.frames[i.index] = 0; data.animation_pos[i.index] = 0; }

std::uint8_t                                                    Game::ECS::Components::AnimationManager::get_frames(Instance& i) { return data.frames[i.index]; }
void                                                            Game::ECS::Components::AnimationManager::set_frames(Instance& i, std::uint8_t x) { data.frames[i.index] = x; }

std::vector<Game::ECS::Components::AnimationManager::Animation> Game::ECS::Components::AnimationManager::get_animations(Instance& i) { return data.animations[i.index]; }
void                                                            Game::ECS::Components::AnimationManager::set_animations(Instance& i, std::vector<Animation> x) { (data.animations[i.index]).swap(x); }
void                                                            Game::ECS::Components::AnimationManager::add_animation(Instance& i, Animation a) { data.animations[i.index].push_back(a); }

std::uint8_t                                                    Game::ECS::Components::AnimationManager::get_animation_pos(Instance& i) { return data.animation_pos[i.index]; }
void                                                            Game::ECS::Components::AnimationManager::set_animation_pos(Instance& i, std::uint8_t x) { data.animation_pos[i.index] = x; }

/*
 * ========================================
 * Component handling
 * ========================================
 */
Game::ECS::Components::AnimationManager::Instance Game::ECS::Components::AnimationManager::add_component(const Entity& e)
{
  // TODO: Do some fancy allocation stuff here instead of allocating every time something is added
  allocate(data.instances + 1);

  data.entity[data.instances] = e;

  map.insert({ e, data.instances });

  data.state[data.instances] = 0;
  data.frames[data.instances] = 0;
  data.animation_pos[data.instances] = 0;

  return { data.instances++ };
}

void Game::ECS::Components::AnimationManager::destroy_component(Instance& i)
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
  data.state[i.index] = data.state[last_index];
  data.frames[i.index] = data.frames[last_index];
  data.animation_pos[i.index] = data.animation_pos[last_index];
  data.animations[i.index] = data.animations[last_index];

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
void Game::ECS::Components::AnimationManager::allocate(std::uint32_t size)
{
  // Expensive operation, only allocate when needed
  if (size <= data.instances)
    return;

  Data new_data;

  unsigned int bytes = size * (sizeof(Entity) + 3 * sizeof(std::uint8_t));
  new_data.buffer = std::malloc(bytes);
  new_data.instances = data.instances;
  new_data.allocated = size;

  // Set the pointers to the locations in the buffer
  new_data.entity = reinterpret_cast<Entity*>(new_data.buffer);
  new_data.state = reinterpret_cast<std::uint8_t*>(new_data.entity + size);
  new_data.frames = new_data.state + size;
  new_data.animation_pos = reinterpret_cast<std::uint8_t*>(new_data.frames + size);
  
  new_data.animations = new std::vector<Animation>[size];

  // Copy the old data into the new buffer
  std::memcpy(new_data.entity,        data.entity,        data.instances * sizeof(Entity));
  std::memcpy(new_data.state,         data.state,         data.instances * sizeof(std::uint8_t));
  std::memcpy(new_data.frames,        data.frames,        data.instances * sizeof(std::uint8_t));
  std::memcpy(new_data.animation_pos, data.animation_pos, data.instances * sizeof(std::uint8_t));

  std::memcpy(new_data.animations, data.animations, data.instances * sizeof(std::vector<Animation>));

  std::free(data.buffer);
  delete[] data.animations;

  data = new_data;
}
