#ifndef SKIDIBIDIBOP_GAME_PLAYER
#define SKIDIBIDIBOP_GAME_PLAYER

#include "core_object.h"
#include "core.h"

namespace Game
{
  namespace Player
  {
    class Object : public Core::Object::Object
    {
    public:
      Object(SDL::Renderer*);
      void update();
    private:
      Core::Directions direction;
      struct
      {
        int x, y;
      } Position;
      struct
      {
        int x, y;
      } Velocity;
      bool moving;

      void setDirection();
      void move();
    };
  };
};

#endif
