#ifndef SKIDIBIDIBOP_GAME_MAP_TILE
#define SKIDIBIDIBOP_GAME_MAP_TILE

#include "core_object.h"

namespace Game
{
  namespace Map
  {
    class Tile : public Core::Object::Object
    {
    public:
      struct Collision
      {
        bool top;
        bool bottom;
        bool left;
        bool right;
      };

      // The x and y are temporary until there is a better solution found
      Tile(SDL::Renderer*, unsigned int id, Collision, unsigned int state, int x, int y);

      void update();
    private:
      unsigned int id;
      Collision collision;
      unsigned int state;
    };
  };
};

#endif
