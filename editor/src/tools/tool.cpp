#include "tool.h"
#include <SDL2/SDL_ttf.h>
#include "utility.h"

Editor::Tool::Base::Base(SDLW::Renderer* renderer_p, const std::string& text_p, int x_p, int y_p)
{
  renderer = renderer_p;
  text = text_p;
  x = x_p;
  y = y_p;
  destRect = {x_p, y_p, 0, 0};
  texture = Utility::create_text_center(renderer, text, destRect, WIDTH, HEIGHT, {255, 255, 255});
}

Editor::Tool::Base::~Base()
{

}

void Editor::Tool::Base::draw()
{
  renderer->copy(texture, 0, &destRect);
}
