#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEM_MENU_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEM_MENU_SYSTEM

#include "system.h"
#include "sdlw.h"

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class Menu : public System
      {
      public:
        static void update();
        static void draw(SDLW::Renderer*);
      private:
        static int panel;
        static int slot_selected_left, slot_selected_right;
        static int slot_chosen_left;
      };

      extern Manager::RegisterSystem<Menu> menu_system;
    };
  };
};

#endif
