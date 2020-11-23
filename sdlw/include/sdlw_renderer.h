#ifndef SDLW_RENDERER
#define SDLW_RENDERER

#include <SDL2/SDL.h>
#include "sdlw_window.h"

namespace SDLW
{
  class Texture;

  class Renderer
  {
  public:
    Renderer(Window* window);
    ~Renderer();

    void present();
    void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void clear();
    void copy(Texture*, SDL_Rect* srcRect, SDL_Rect* destRect);

    SDL_Renderer* get_SDL();
  private:
    SDL_Renderer* renderer;
  };
};

#endif
