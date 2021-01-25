#include "menu_system.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Menu> Game::ECS::Systems::menu_system;

void Game::ECS::Systems::Menu::update()
{

}

void Game::ECS::Systems::Menu::draw(SDLW::Renderer* renderer)
{
  renderer->set_draw_color(0, 0, 0, 128);
  SDL_RenderFillRect(renderer->get_SDL(), nullptr);
}
