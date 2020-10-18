#include "tool.h"
#include <SDL2/SDL_ttf.h>

#include "window.h"

Editor::Tool::Tab::Tab(SDLW::Renderer* renderer, const std::string& text, int x, int y, SDL_Color color)
{
  this->text = text;
  this->x = x;
  this->y = y;
  this->color = color;
  this->renderer = renderer;

  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txtSurface = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
  texture = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->getSDL(), txtSurface));
  SDL_FreeSurface(txtSurface);
  TTF_CloseFont(font);
}

Editor::Tool::Tab::~Tab()
{
/*  for (Base* t : tools)
    delete t;

  tools.clear();*/
}

void Editor::Tool::Tab::update(MouseState ms)
{

}

void Editor::Tool::Tab::draw()
{
  SDL_Rect dRect = {x, y, 64, 32};
  renderer->setDrawColor(color.r, color.g, color.b, 255);
  SDL_RenderFillRect(renderer->getSDL(), &dRect);
  SDL_QueryTexture(texture->getSDL(), NULL, NULL, &dRect.w, &dRect.h);
  dRect.x += (64 - dRect.w) / 2;
  dRect.y += (32 - dRect.h) / 2;
  renderer->copy(texture, 0, &dRect);
}

bool Editor::Tool::Tab::isHovered(int mx, int my)
{
  return mx >= x && mx <= x + 64 && my >= y && my <= y + 32; 
}
