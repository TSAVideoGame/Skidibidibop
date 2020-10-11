#include "player_manager.h"
#include "player_object.h"

Game::Player::Manager::Manager(SDL::Renderer* renderer) : Core::Object::Manager()
{
  objects.push_back(new Object(renderer));
}
