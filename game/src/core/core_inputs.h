#ifndef SKIDIBIDIBOP_GAME_CORE_INPUTS
#define SKIDIBIDIBOP_GAME_CORE_INPUTS

#include <SDL2/SDL.h>

namespace Game
{
  namespace Core
  {
    namespace Inputs
    {
      struct Pressed
      {
        bool up, right, down, left, slot_a, slot_b, slot_c, mouse_down;
      };

      enum Keys {
        UP_KEY     = SDLK_w,
        RIGHT_KEY  = SDLK_d,
        DOWN_KEY   = SDLK_s,
        LEFT_KEY   = SDLK_a,
        SLOT_A_KEY = SDLK_1,
        SLOT_B_KEY = SDLK_2,
        SLOT_C_KEY = SDLK_3
      };
    }
  };
};

#endif
