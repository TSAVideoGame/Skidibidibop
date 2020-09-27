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
  SDL_Rect dRect = {destRect.x - Core::camera.x, destRect.y - Core::camera.y, destRect.w, destRect.h};
  renderer->copy(Core::Core::getTexture(), &srcRect, &dRect);
}
