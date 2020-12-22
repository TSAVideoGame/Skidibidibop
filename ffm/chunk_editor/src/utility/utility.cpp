#include "utility.h"
#include <SDL2/SDL_ttf.h>

SDLW::Texture* FFM::ChunkEditor::Utility::create_text_center(SDLW::Renderer* renderer, const std::string& text, SDL_Rect& destRect, int w, int h, SDL_Color color)
{
  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txt_surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDLW::Texture* texture = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txt_surface));
  SDL_FreeSurface(txt_surface);
  TTF_CloseFont(font);

  SDL_QueryTexture(texture->get_SDL(), 0, 0, &destRect.w, &destRect.h);
  destRect.x += (w - destRect.w) / 2;
  destRect.y += (h - destRect.h) / 2;

  return texture;
}
