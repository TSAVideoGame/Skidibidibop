#include "sdlw_renderer.h"
#include "sdlw_texture.h"

SDLW::Renderer::Renderer(Window* window)
{
  renderer = SDL_CreateRenderer(window->getSDL(), -1, 0);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  clear();
  present();
}

SDLW::Renderer::~Renderer()
{
  SDL_DestroyRenderer(renderer);
}

void SDLW::Renderer::present()
{
  SDL_RenderPresent(renderer);
}

void SDLW::Renderer::set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SDLW::Renderer::clear()
{
  SDL_RenderClear(renderer);
}

void SDLW::Renderer::copy(Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect)
{
  SDL_RenderCopy(renderer, texture->getSDL(), srcRect, destRect);
}

SDL_Renderer* SDLW::Renderer::getSDL()
{
  return renderer;
}
