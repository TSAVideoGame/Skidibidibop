#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_RENDER_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_RENDER_SYSTEM

#include "system.h"

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class Render : public System
      {
      public:
        static void draw();
        void register_functions();
      };

      extern Manager::RegisterSystem<Render> render_system;
    };
  };
};

#endif
