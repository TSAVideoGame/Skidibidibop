#include "test_scene.h"
#include "entity.h"
#include "render_component.h"
#include "render_system.h"

Game::Scenes::Manager::RegisterScene<Game::Scenes::TestScene> testScene;

Game::Scenes::TestScene::TestScene()
{
  // In real siutation stuff like player should be pointer data member so you can use it between methods
  ECS::Entity player = ECS::EntityManager::get_instance().create_entity();

  ECS::Components::RenderManager* rm = ECS::Components::Manager::get_instance().get_component<ECS::Components::RenderManager>();
  ECS::Components::RenderManager::Instance rmi = rm->add_component(player);

  SDL_Rect src_rect = {0, 6 * 32, 32, 32};
  rm->set_src_rect(rmi, src_rect);
  SDL_Rect dest_rect = {0, 0, 32, 32};
  rm->set_dest_rect(rmi, dest_rect);
}

Game::Scenes::TestScene::~TestScene()
{
  
}

void Game::Scenes::TestScene::update()
{
  
}

void Game::Scenes::TestScene::draw(SDLW::Renderer* renderer)
{
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Render>()->draw(renderer); 
}
