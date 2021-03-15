#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_LINE_DEBUG_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_LINE_DEBUG_SYSTEM

#include "system.h"
#include "sdlw.h"

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class LineDebug : public System
      {
      public:
        static void draw(SDLW::Renderer*);
      };

      extern Manager::RegisterSystem<LineDebug> line_debug_system;
    };
  };
};

#endif
