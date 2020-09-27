#include "texture.h"
#include <SDL2/SDL_image.h>
#include "renderer.h"

/*
 * ========================================
 * This is an expensive operation, use it
 * sparsely
 * ========================================
 */
Game::SDL::Texture::Texture(const char* filePath, Renderer* renderer)
{
  SDL_Surface* tempSurface = IMG_Load(filePath);
  texture = SDL_CreateTextureFromSurface(renderer->getSDL(), tempSurface);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  SDL_FreeSurface(tempSurface);
}

Game::SDL::Texture::~Texture()
{
  SDL_DestroyTexture(texture);
}

SDL_Texture* Game::SDL::Texture::getSDL()
{
  return texture;
}
