#ifndef SKIDIBIDIBOP_GAME_PLAYER
#define SKIDIBIDIBOP_GAME_PLAYER

#include "core_object.h"
#include "core.h"

namespace Game
{
  namespace Player
  {
    struct Position
    {
      int x, y;
    };

    struct Velocity
    {
      float x, y;
    };

    class Object : public Core::Object::Object
    {
    public:
      Object(SDLW::Renderer*);
      void update();
    private:
      static float maxVelocity;

      Position position;
      Velocity velocity;
      Core::Directions direction;
      bool moving;

      void setDirection();
      void move();
      void prepareDraw();
    };
  };
};

#endif
