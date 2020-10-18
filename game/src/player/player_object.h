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
      Object(SDLW::Renderer*);
      void update();
    private:
      static float maxVelocity;

      Core::Directions direction;
      struct
      {
        int x, y;
      } Position;
      struct
      {
        float x, y;
      } Velocity;
      bool moving;

      void setDirection();
      void move();
      void prepareDraw();
    };
  };
};

#endif
