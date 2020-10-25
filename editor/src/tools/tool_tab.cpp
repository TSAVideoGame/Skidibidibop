#include "tool.h"
#include "tool_main.h"
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "window.h"

Editor::Tool::Tab::Tab(SDLW::Renderer* renderer, const std::string& text, int x, int y, SDL_Color color)
{
  this->text = text;
  this->x = x;
  this->y = y;
  this->color = color;
  this->renderer = renderer;

  isSelected = false;

  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txtSurface = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
  texture = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->getSDL(), txtSurface));
  SDL_FreeSurface(txtSurface);
  TTF_CloseFont(font);
}

Editor::Tool::Tab::~Tab()
{
  for (Base* t : tools)
    delete t;

  tools.clear();
}

void Editor::Tool::Tab::update(MouseState ms, Inputs inputs)
{
  if (isSelected)
  {
    for (Base* t : tools)
      t->update(ms, inputs);
  }
}

void Editor::Tool::Tab::draw()
{
  // Draw self
  SDL_Rect dRect = {x, y, 64, 32};
  renderer->setDrawColor(color.r, color.g, color.b, 255);
  SDL_RenderFillRect(renderer->getSDL(), &dRect);
  SDL_QueryTexture(texture->getSDL(), NULL, NULL, &dRect.w, &dRect.h);
  dRect.x += (64 - dRect.w) / 2;
  dRect.y += (32 - dRect.h) / 2;
  renderer->copy(texture, 0, &dRect);

  if (isSelected)
  {
    // Draw tools
    for (Base* t : tools)
      t->draw();
  }
}

bool Editor::Tool::Tab::isHovered(int mx, int my)
{
  return mx >= x && mx <= x + 64 && my >= y && my <= y + 32; 
}

// Main tab
Editor::Tool::Tabs::Main::Main(SDLW::Renderer* renderer, const std::string& text, int x, int y, SDL_Color color) : Tab(renderer, text, x, y, color)
{
  tools.push_back(new Tool::Main::Save(renderer, 0, Constants::Window.height - Constants::Window.toolBarHeight));
  tools.push_back(new Tool::Main::Load(renderer, 0, Constants::Window.height - Constants::Window.toolBarHeight + Base::HEIGHT * 1));
  tools.push_back(new Tool::Main::Col(renderer, 0, Constants::Window.height - Constants::Window.toolBarHeight + Base::HEIGHT * 2));
  tools.push_back(new Tool::Main::Row(renderer, 0, Constants::Window.height - Constants::Window.toolBarHeight + Base::HEIGHT * 3));
}
