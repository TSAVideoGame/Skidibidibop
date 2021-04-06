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
      bool slot_a, slot_b, slot_c, slot_d;
      bool attack;
      bool pause;
      int mouse_x, mouse_y;
      bool mouse_down;
      bool space;
    };

    struct KeyBindings
    {
      SDL_Keycode up     = SDLK_w;
      SDL_Keycode right  = SDLK_d;
      SDL_Keycode down   = SDLK_s;
      SDL_Keycode left   = SDLK_a;

      SDL_Keycode slot_a = SDLK_1;
      SDL_Keycode slot_b = SDLK_2;
      SDL_Keycode slot_c = SDLK_3;
      SDL_Keycode slot_d = SDLK_4;

      SDL_Keycode attack = SDLK_o;
      SDL_Keycode talk =   SDLK_p;

      SDL_Keycode pause = SDLK_RETURN;
      SDL_Keycode space = SDLK_SPACE;
    };
  };
};

#endif
