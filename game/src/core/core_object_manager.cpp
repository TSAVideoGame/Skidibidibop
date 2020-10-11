#include "core_object_manager.h"

Game::Core::Object::Manager::Manager()
{

}

Game::Core::Object::Manager::~Manager()
{
  empty();
}

void Game::Core::Object::Manager::update()
{
  for (Base* o : objects)
    o->update();
}

void Game::Core::Object::Manager::draw()
{
  for (Base* o : objects)
    o->draw();
}

void Game::Core::Object::Manager::empty()
{
  for (Base* o : objects)
    delete o;
  objects.clear();
}
