#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_COLLISION_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_COLLISION_SYSTEM

#include "system.h"
#include <cstdint>
#include "entity.h"

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class Collision : public System
      {
      public:
        static void update();
      private:
        struct AABB
        {
          std::uint32_t x;
          std::uint32_t y;
          std::uint32_t w;
          std::uint32_t h;
        };

        static AABB get_AABB(Entity);
      };

      extern Manager::RegisterSystem<Collision> collision_system;
    };
  };
};

#endif
