#include "player_object.h"

Game::Player::Object::Object(SDL::Renderer* renderer) : Core::Object::Object(renderer)
{
  Position = {0, 0};
  Velocity = {0, 0};
}

void Game::Player::Object::update()
{
  setDirection();
  move();
}

void Game::Player::Object::setDirection()
{
  if (Core::Core::getInputs().up || Core::Core::getInputs().right || Core::Core::getInputs().down || Core::Core::getInputs().left)
  {
    moving = true;
    // Not optimized, just working for now
    if (Core::Core::getInputs().up)
    {
      if (Core::Core::getInputs().right || Core::Core::getInputs().left)
      {
        if (Core::Core::getInputs().right)
          direction = Core::Directions::TOP_RIGHT;
        else
          direction = Core::Directions::TOP_LEFT;
      }
      else
      {
        direction = Core::Directions::TOP;
      }
    }
    else if (Core::Core::getInputs().right)
    {
      if (Core::Core::getInputs().down)
        direction = Core::Directions::BOTTOM_RIGHT;
      else
        direction = Core::Directions::RIGHT;
    }
    else if (Core::Core::getInputs().down)
    {
      if (Core::Core::getInputs().left)
        direction = Core::Directions::BOTTOM_LEFT;
      else
        direction = Core::Directions::BOTTOM; 
    }
    else // if (Core::Core::getInputs().left)
    {
      direction = Core::Directions::LEFT;
    }
  }
  else
  {
    moving = false;
  }
}

void Game::Player::Object::move()
{
  if (moving)
  {
    Position.x += Velocity.x;
    Position.y += Velocity.y;
  }
  else
  {
    Velocity.x /= 2;
    Velocity.y /= 2;
  }
}
