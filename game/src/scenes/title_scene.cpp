#include "title_scene.h"
#include "core.h"
#include "test_scene.h"

Game::Scenes::Manager::RegisterScene<Game::Scenes::Title> Game::Scenes::title_scene;

static SDLW::Texture* title_image = nullptr;
static SDLW::Texture* title_text = nullptr;

Game::Scenes::Title::Title()
{

}

Game::Scenes::Title::~Title()
{
  if (title_image != nullptr)
    delete title_image;
}

static int ticks = 0;
static int title_y = 0;
void Game::Scenes::Title::update()
{
  ++ticks; 

  Input::Data in = Core::get_inputs();

  if (in.space)
  {
    Scenes::Manager::get_instance().set_scene(Scenes::Manager::get_instance().get_scene<TestScene>());
  }

  title_y = 16 * std::sin(1.0 / 30 * ticks) - 16;
}

void Game::Scenes::Title::draw(SDLW::Renderer* renderer)
{
  if (title_image == nullptr)
  {
    title_image = new SDLW::Texture("res/title.png", renderer);
    title_text = new SDLW::Texture("res/title_text.png", renderer);
  }

  SDL_Rect dest_rect = { -16, title_y, 992, 672 };

  renderer->copy(title_image, 0, &dest_rect);
  renderer->copy(title_text, 0, 0);
}
