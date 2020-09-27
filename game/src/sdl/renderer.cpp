#include "renderer.h"
#include "texture.h"

Game::SDL::Renderer::Renderer(Window* window)
{
  renderer = SDL_CreateRenderer(window->getSDL(), -1, 0);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  clear();
  present();
}

Game::SDL::Renderer::~Renderer()
{
  SDL_DestroyRenderer(renderer);
}

void Game::SDL::Renderer::present()
{
  SDL_RenderPresent(renderer);
}

void Game::SDL::Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Game::SDL::Renderer::clear()
{
  SDL_RenderClear(renderer);
}

void Game::SDL::Renderer::copy(Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect)
{
  SDL_RenderCopy(renderer, texture->getSDL(), srcRect, destRect);
}

SDL_Renderer* Game::SDL::Renderer::getSDL()
{
  return renderer;
}
