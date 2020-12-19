#ifndef SKIDIBIDIBOP_GAME_CORE_INPUT
#define SKIDIBIDIBOP_GAME_CORE_INPUT

#include "sdlw.h"

namespace Game
{
  namespace Input
  {
    struct Data
    {
      bool up, right, down, left;
      bool slot_a, slot_b, slot_c;
      bool attack;
      bool pause;
    };

    struct KeyBindings
    {
      SDL_Keycode up     = SDLK_w;
      SDL_Keycode right  = SDLK_d;
      SDL_Keycode down = SDLK_s;
      SDL_Keycode left   = SDLK_a;

      SDL_Keycode slot_a = SDLK_1;
      SDL_Keycode slot_b = SDLK_2;
      SDL_Keycode slot_c = SDLK_3;

      SDL_Keycode attack = SDLK_o;

      SDL_Keycode pause = SDLK_RETURN;
    };
  };
};

#endif
