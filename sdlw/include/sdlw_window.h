#ifndef SDLW_WINDOW
#define SDLW_WINDOW

#include <SDL2/SDL.h>

namespace SDLW
{
  class Window
  {
  public:
    Window(const char* title, int x, int y, int w, int h, int flags);
    ~Window();

    SDL_Window* get_SDL();
  private:
    SDL_Window* window;
  };
};

#endif
