#include "entity.h"

Game::ECS::EntityManager& Game::ECS::EntityManager::get_instance()
{
  static EntityManager instance;
  return instance;
}

/*
 * ========================================
 * EntityManager::create_entity
 *
 * Allows entities to be created from
 * outside the class
 * ========================================
 */
Game::ECS::Entity Game::ECS::EntityManager::create_entity()
{
  std::uint32_t index;

  if (empty_indices.size() > MIN_EMPTY_INDICES)
  {
    index = empty_indices.front();
    empty_indices.pop_front();
  }
  else
  {
    generations.push_back(0);
    index = generations.size() - 1;
    // TODO: Figure out a way to deal with this problem (too many entities are made)
    // assert(index < (1 << Entity::INDEX_BITS), "Exceeded entity limit");
  }

  return build_entity(index, generations[index]);
}

/*
 * ========================================
 * EntityManager::destory_entity
 *
 * 'Destroys' an entity
 * Since entities are weak references, it
 * just changes the generation
 * ========================================
 */
void Game::ECS::EntityManager::destory_entity(Entity& e)
{
  if (is_alive(e))
    return;

  // Increase the generation of the index where the entity is stored
  // and mark the index as open by pushing it into the deque
  ++generations[e.get_index()];
  empty_indices.push_back(e.get_index());
}

/*
 * ========================================
 * EntityManager::is_alive
 *
 * Checks if an entity is alive
 * ========================================
 */
bool Game::ECS::EntityManager::is_alive(const Entity& e)
{
  // For an entity to be alive the generations will be the same
  return generations[e.get_index()] == e.get_generation();
}

/*
 * ========================================
 * EntityManager::build_entity
 *
 * Properly constructs an entity
 * Basically a helper function for
 * create_entity
 * ========================================
 */
Game::ECS::Entity Game::ECS::EntityManager::build_entity(std::uint32_t index, std::uint32_t generation)
{
  return Entity {(generation << Entity::INDEX_BITS) | index};
}
