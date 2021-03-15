#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_ANIMATION_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_ANIMATION_SYSTEM

#include "system.h"
#include "sdlw.h"

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class Animation : public System
      {
      public:
        static void update();
      };

      extern Manager::RegisterSystem<Animation> animation_system;
    };
  };
};

#endif
