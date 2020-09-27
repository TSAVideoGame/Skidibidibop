#include "core_object.h"
#include "core.h"

Game::Core::Object::Base::~Base()
{

}

Game::Core::Object::Object::Object(SDL::Renderer* renderer)
{
  this->renderer = renderer;
}

Game::Core::Object::Object::~Object()
{
}

void Game::Core::Object::Object::draw()
{
  renderer->copy(Core::Core::getTexture(), &srcRect, &destRect);
}
