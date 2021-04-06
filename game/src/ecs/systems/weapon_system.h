#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_WEAPON_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_WEAPON_SYSTEM

#include "system.h"
#include "sdlw.h"
#include <vector>
#include "entity.h"

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class Weapon : public System
      {
      public:
        void init();
        static std::vector<Entity> weapons;
        static std::vector<Entity> projectiles; // Projectile Defs
      };

      extern Manager::RegisterSystem<Weapon> weapon_system;
    };
  };
};

#endif
