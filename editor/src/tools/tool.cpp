#include "tool.h"
#include <SDL2/SDL_ttf.h>

#include <iostream>

Editor::Tool::Base::Base(SDLW::Renderer* renderer, const std::string& text, int x, int y)
{
  this->renderer = renderer;
  this->text = text;
  this->x = x;
  this->y = y;

  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txtSurface = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
  texture = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->getSDL(), txtSurface));
  SDL_FreeSurface(txtSurface);
  TTF_CloseFont(font);

  destRect = {x, y, 0, 0};
  SDL_QueryTexture(texture->getSDL(), 0, 0, &destRect.w, &destRect.h);
  destRect.x += (WIDTH - destRect.w) / 2;
  destRect.y += (HEIGHT - destRect.h) / 2;
}

Editor::Tool::Base::~Base()
{

}

void Editor::Tool::Base::update(MouseState ms, Inputs inputs)
{

}

void Editor::Tool::Base::draw()
{
  renderer->copy(texture, 0, &destRect);
}
