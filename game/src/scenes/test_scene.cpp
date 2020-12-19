#include "test_scene.h"
#include "entity.h"
#include "render_component.h"
#include "render_system.h"
#include "core.h"

static Game::ECS::Entity player = Game::ECS::EntityManager::get_instance().create_entity();

Game::Scenes::Manager::RegisterScene<Game::Scenes::TestScene> testScene;

Game::Scenes::TestScene::TestScene()
{

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
  ECS::Components::RenderManager* rm = ECS::Components::Manager::get_instance().get_component<ECS::Components::RenderManager>();
  ECS::Components::RenderManager::Instance rmi = rm->get_instance(player);
  // Testing input, really should change transform/physics component, then all the dest_rects should be updated
  if (Core::get_inputs().up)
  {
    rm->data.dest_rect[rmi.index].y -= 5;
  }
  if (Core::get_inputs().right)
  {
    rm->data.dest_rect[rmi.index].x += 5;
  }
  if (Core::get_inputs().down)
  {
    rm->data.dest_rect[rmi.index].y += 5;
  }
  if (Core::get_inputs().left)
  {
    rm->data.dest_rect[rmi.index].x -= 5;
  }
}

void Game::Scenes::TestScene::draw(SDLW::Renderer* renderer)
{
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Render>()->draw(renderer); 
}
