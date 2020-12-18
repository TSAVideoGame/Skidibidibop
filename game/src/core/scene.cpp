#include "scene.h"
#include "system.h"
#include "render_system.h"

/*
 * ========================================
 * Scene
 * ========================================
 */
Game::Scenes::Scene::Scene()
{

}

Game::Scenes::Scene::~Scene()
{

}

void Game::Scenes::Scene::draw(SDLW::Renderer* renderer)
{
  ECS::Systems::Manager::get_instance().get_system<ECS::Systems::Render>()->draw(renderer); 
}

/*
 * ========================================
 * SceneManager
 * ========================================
 */
Game::Scenes::Manager& Game::Scenes::Manager::get_instance()
{
  static Manager instance;
  return instance;
}

void Game::Scenes::Manager::set_scene(Scene* s)
{
  // TODO: Fancily transition scenes
  current_scene = s;
}

void Game::Scenes::Manager::update()
{
  current_scene->update();
}

void Game::Scenes::Manager::draw(SDLW::Renderer* renderer)
{
  current_scene->draw(renderer);
}

Game::Scenes::Manager::Manager()
{

}

Game::Scenes::Manager::~Manager()
{
  for (Scene* s : scenes)
    delete s;
}

/*
 * ========================================
 * Void scene
 * ========================================
 */
Game::Scenes::Manager::RegisterScene<Game::Scenes::Void> void_scene;
