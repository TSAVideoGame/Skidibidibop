#include "player_object.h"

float Game::Player::Object::maxVelocity = 10;

Game::Player::Object::Object(SDLW::Renderer* renderer) : Core::Object::Object(renderer),
  position({0, 0}),
  velocity({0, 0}),
  direction(Core::DIR_BOTTOM)
{
  srcRect = {0, 32, 32, 32};
  destRect = {position.x, position.y, 32, 32};
}

void Game::Player::Object::update()
{
  setDirection();
  move();
  prepareDraw();
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
          direction = Core::DIR_TOP_RIGHT;
        else
          direction = Core::DIR_TOP_LEFT;
      }
      else
      {
        direction = Core::DIR_TOP;
      }
    }
    else if (Core::Core::getInputs().right)
    {
      if (Core::Core::getInputs().down)
        direction = Core::DIR_BOTTOM_RIGHT;
      else
        direction = Core::DIR_RIGHT;
    }
    else if (Core::Core::getInputs().down)
    {
      if (Core::Core::getInputs().left)
        direction = Core::DIR_BOTTOM_LEFT;
      else
        direction = Core::DIR_BOTTOM; 
    }
    else // if (Core::Core::getInputs().left)
    {
      direction = Core::DIR_LEFT;
    }
  }
  else
  {
    moving = false;
  }
}

void Game::Player::Object::move()
{
  // Handle setting velocities
  // Remember y-axis is flipped
  // This section could be done better to reduce redundancy
  const float velIncrease = 0.2; // This should be another static variable
  if (moving)
  {
    switch (direction)
    {
      case Core::DIR_TOP:
      {
        if (velocity.y > -maxVelocity)
          velocity.y -= velIncrease;

        velocity.x /= 2;

        break;
      }
      case Core::DIR_TOP_RIGHT:
      {
        if (velocity.y > -maxVelocity)
          velocity.y -= velIncrease;

        if (velocity.x < maxVelocity)
          velocity.x += velIncrease;
        
        break;
      }
      case Core::DIR_RIGHT:
      {
        if (velocity.x < maxVelocity)
          velocity.x += velIncrease;

        velocity.y /= 2;

        break;
      }
      case Core::DIR_BOTTOM_RIGHT:
      {
        if (velocity.y < maxVelocity)
          velocity.y += velIncrease;

        if (velocity.x < maxVelocity)
          velocity.x += velIncrease;

        break;
      }
      case Core::DIR_BOTTOM:
      {
        if (velocity.y < maxVelocity)
          velocity.y += velIncrease;

        velocity.x /= 2;

        break;
      }
      case Core::DIR_BOTTOM_LEFT:
      {
        if (velocity.y < maxVelocity)
          velocity.y += velIncrease;

        if (velocity.x > -maxVelocity)
          velocity.x -= velIncrease;

        break;
      }
      case Core::DIR_LEFT:
      {
        if (velocity.x > -maxVelocity)
          velocity.x -= velIncrease;

        velocity.y /= 2;
      }
      case Core::DIR_TOP_LEFT:
      {
        if (velocity.y > -maxVelocity)
          velocity.y -= velIncrease;

        if (velocity.x > -maxVelocity)
          velocity.x -= velIncrease;

        break;
      }
    }
  }
  // Handle actual movement
  if (moving)
  {
    position.x += velocity.x;
    position.y += velocity.y;
  }
  else
  {
    velocity.x /= 2;
    velocity.y /= 2;
  }
}

void Game::Player::Object::prepareDraw()
{
  srcRect = {0, direction * 32 + 32, 32, 32};
  destRect.x = position.x;
  destRect.y = position.y;
}
