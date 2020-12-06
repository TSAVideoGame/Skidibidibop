#include "render_system.h"
#include <iostream>

//Game::ECS::Systems::Manager::register_system(new Game::ECS::Systems::Render());

void Game::ECS::Systems::Render::draw()
{
  std::cout << "Drawing" << std::endl;
}

void Game::ECS::Systems::Render::register_functions()
{
  Manager::register_draw(draw); 
}
