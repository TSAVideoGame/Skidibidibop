#ifndef SDLW_TEXTURE
#define SDLW_TEXTURE

#include <SDL2/SDL.h>

namespace SDLW
{
  class Renderer;

  class Texture
  {
  public:
    Texture(SDL_Texture*);
    Texture(const char*, Renderer*);
    ~Texture();

    SDL_Texture* getSDL();
  private:
    SDL_Texture* texture;
  };
};

#endif
