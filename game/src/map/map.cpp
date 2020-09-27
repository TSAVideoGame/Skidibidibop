#include "map.h"

Game::Map::Manager::Manager(SDL::Renderer* ren, Data::Types::Map data)
{
  tiles.reserve(data.size.x * data.size.y);

  for (unsigned int i = 0; i < data.size.x * data.size.y; i++)
  {
    Data::Types::Map::Tile t = data.tiles[i];
    tiles.push_back(Tile(ren, t.id, {t.Collision.top, t.Collision.bottom, t.Collision.left, t.Collision.right}, t.state, static_cast<unsigned int>(i % data.size.x * 32), static_cast<unsigned int>(i / data.size.x * 32)));
  }
}

Game::Map::Manager::~Manager()
{

}

void Game::Map::Manager::update()
{
  for (Tile t : tiles)
    t.update();
}

void Game::Map::Manager::draw()
{
  for (Tile t : tiles)
    t.draw();
}
