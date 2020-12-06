#ifndef SKIDIBIDIBOP_GAME_ECS_ENTITIY
#define SKIDIBIDIBOP_GAME_ECS_ENTITIY

#include <cstdint>
#include <vector>
#include <deque>
#include <functional>

namespace Game
{
  namespace ECS
  {
    struct Entity
    {
      static const std::uint8_t INDEX_BITS = 24;
      static const std::uint32_t INDEX_MASK = (1 << INDEX_BITS) - 1; // this turns on all bits 0 - INDEX_BITS (exclusive)
      static const std::uint8_t GENERATION_BITS = 8;
      static const std::uint32_t GENERATION_MASK = (1 << GENERATION_BITS) - 1;

      std::uint32_t id;

      std::uint32_t get_index() const { return id & INDEX_MASK; }
      std::uint32_t get_generation() const { return (id >> INDEX_BITS) & GENERATION_MASK; }

      bool operator ==(const Entity& e) const { return id == e.id; }
    };

    class EntityManager
    {
    public:
      Entity create_entity();
      void destory_entity(Entity& e);
      bool is_alive(const Entity& e);
    private:
      Entity build_entity(std::uint32_t index, std::uint32_t generation);

      std::vector<std::uint8_t> generations;
      std::deque<std::uint32_t> empty_indices;
      static const std::uint32_t MIN_EMPTY_INDICES = 1 << 10; // This value needs some more thought into it, but should be fine for this game
    };
  };
};

// Hash function for entity so it can be used in unordered maps
namespace std
{
  template<> struct hash<Game::ECS::Entity>
  {
    std::size_t operator()(const Game::ECS::Entity& e) const
    {
      return std::hash<std::uint32_t>{}(e.id);
    }
  };
};

#endif
