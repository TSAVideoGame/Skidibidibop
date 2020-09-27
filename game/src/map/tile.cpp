#include "tile.h"

Game::Map::Tile::Tile(SDL::Renderer* ren, unsigned int id, Collision collision, unsigned int state, int x, int y) : Core::Object::Object(ren)
{
  this->id = id;
  this->collision = collision;
  this->state = state;

  srcRect = {static_cast<int>(32 * id), 0, 32, 32};
  destRect = {x, y, 32, 32};
}

void Game::Map::Tile::update()
{
  // Will do nothing until states / flags are added
}
