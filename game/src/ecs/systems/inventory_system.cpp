#include "inventory_system.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Inventory> inventory_system;

std::uint16_t Game::ECS::Systems::Inventory::slots[] = { 0, 0, 0 };
std::uint8_t Game::ECS::Systems::Inventory::slot_selected = 0;
std::vector<std::uint16_t> Game::ECS::Systems::Inventory::weapons;

void Game::ECS::Systems::Inventory::init()
{
  weapons.push_back(2);
}

void Game::ECS::Systems::Inventory::update()
{

}
