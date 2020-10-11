#include "map.h"

Game::Map::Manager::Manager(SDL::Renderer* ren, const Data::Types::Map& data) : Core::Object::Manager()
{
  renderer = ren;
  loadMap(data);
}

void Game::Map::Manager::loadMap(const Data::Types::Map& data)
{
  for (unsigned int i = 0; i < data.size.x * data.size.y; i++)
  {
    Data::Types::Map::Tile t = data.tiles[i];
    Tile* to = new Tile(Tile(renderer, t.id, {t.Collision.top, t.Collision.bottom, t.Collision.left, t.Collision.right}, t.state, static_cast<unsigned int>(i % data.size.x * 32), static_cast<unsigned int>(i / data.size.x * 32)));
    objects.push_back(to);
  }
}
