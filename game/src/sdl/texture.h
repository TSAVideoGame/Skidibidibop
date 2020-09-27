#ifndef SKIDIBIDIBOP_GAME_SDL_TEXTURE
#define SKIDIBIDIBOP_GAME_SDL_TEXTURE

#include <SDL2/SDL.h>

namespace Game
{
  namespace SDL
  {
    class Renderer;

    class Texture
    {
    public:
      Texture(const char*, Renderer*);
      ~Texture();

      SDL_Texture* getSDL();
    private:
      SDL_Texture* texture;
    };
  };
};

#endif
