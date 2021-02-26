#include "title_scene.h"
#include "core.h"
#include "test_scene.h"

Game::Scenes::Manager::RegisterScene<Game::Scenes::Title> Game::Scenes::title_scene;

static SDLW::Texture* title_image = nullptr;

Game::Scenes::Title::Title()
{

}

Game::Scenes::Title::~Title()
{
  if (title_image != nullptr)
    delete title_image;
}

void Game::Scenes::Title::update()
{
  Input::Data in = Core::get_inputs();

  if (in.attack)
  {
    Scenes::Manager::get_instance().set_scene(Scenes::Manager::get_instance().get_scene<TestScene>());
  }
}

void Game::Scenes::Title::draw(SDLW::Renderer* renderer)
{
  if (title_image == nullptr)
  {
    title_image = new SDLW::Texture("res/title.png", renderer);
  }

  renderer->copy(title_image, 0, 0);
}
