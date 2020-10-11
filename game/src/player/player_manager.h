#ifndef SKIDIBIDIBOP_GAME_PLAYER_MANAGER
#define SKIDIBIDIBOP_GAME_PLAYER_MANAGER

#include "core_object_manager.h"
#include "sdl.h"

namespace Game
{
  namespace Player
  {
    class Manager : public Core::Object::Manager
    {
    public:
      Manager(SDL::Renderer*);
    };
  };
};

#endif
