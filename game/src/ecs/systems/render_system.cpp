#include "render_system.h"
#include <iostream>

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Render> Game::ECS::Systems::render_system;

void Game::ECS::Systems::Render::draw()
{
  std::cout << "Drawing" << std::endl;
}

void Game::ECS::Systems::Render::register_functions()
{
  Manager::get_instance().register_draw(draw); 
}
