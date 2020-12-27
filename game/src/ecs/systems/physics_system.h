#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_PHYSICS_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_PHYSICS_SYSTEM

#include "system.h"
#include "sdlw.h"

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class Physics : public System
      {
      public:
        static void update();
      };

      extern Manager::RegisterSystem<Physics> physics_system;
    };
  };
};

#endif
