#ifndef SKIDIBIDIBOP_GAME_MAP
#define SKIDIBIDIBOP_GAME_MAP

#include "data.h"
#include <vector>
#include "tile.h"
#include "sdl.h"

// Full temporary until I get the Core::Object::Manager situated
namespace Game
{
  namespace Map
  {
    class Manager
    {
    public:
      Manager(SDL::Renderer*, Data::Types::Map);
      ~Manager();

      void update();
      void draw();
    private:
      std::vector<Tile> tiles;
    };
  };
};

#endif
