#ifndef SKIDIBIDIBOP_GAME_SDL_RENDERER
#define SKIDIBIDIBOP_GAME_SDL_RENDERER

#include <SDL2/SDL.h>
#include "window.h"

namespace Game
{
  namespace SDL
  {
    class Texture;

    class Renderer
    {
    public:
      Renderer(Window* window);
      ~Renderer();

      void present();
      void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
      void clear();
      void copy(Texture*, SDL_Rect* srcRect, SDL_Rect* destRect);

      SDL_Renderer* getSDL();
    private:
      SDL_Renderer* renderer;
    };
  };
};

#endif
