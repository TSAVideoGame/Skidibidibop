#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_RENDER_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_RENDER_SYSTEM

#include "system.h"
#include "sdlw.h"

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class Render : public System
      {
      public:
        static void draw(SDLW::Renderer*);
        void register_functions();
      };

      extern Manager::RegisterSystem<Render> render_system;
    };
  };
};

#endif
