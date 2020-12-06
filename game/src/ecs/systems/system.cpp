#include "system.h"

/*
 * ========================================
 * Systems::Manager
 * ========================================
 */
Game::ECS::Systems::ManagerData Game::ECS::Systems::Manager::data;

void Game::ECS::Systems::Manager::init()
{
  for (System* s : data.systems)
    s->register_functions();
}

void Game::ECS::Systems::Manager::close()
{
  for (System* s : data.systems)
    delete s;
}

void Game::ECS::Systems::Manager::update()
{
  for (void(*f)() : data.update_functions)
    f();
}

void Game::ECS::Systems::Manager::draw()
{
  for (void(*f)() : data.draw_functions)
    f();
}

/*
 * ========================================
 * Register functions
 *
 * These don't deal with CPU registers, they
 * are just registering (the verb) the systems
 * ========================================
 */
void Game::ECS::Systems::Manager::register_system(System* s)
{
  data.systems.push_back(s);
}

void Game::ECS::Systems::Manager::register_update(void(*f)())
{
  data.update_functions.push_back(f);
}

void Game::ECS::Systems::Manager::register_draw(void(*f)())
{
  data.draw_functions.push_back(f);
}
