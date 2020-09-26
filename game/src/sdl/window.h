#ifndef SKIDIBIDIBOP_GAME_SDL_WINDOW
#define SKIDIBIDIBOP_GAME_SDL_WINDOW

#include <SDL2/SDL.h>

namespace Game
{
  namespace SDL
  {
    class Window
    {
    public:
      Window(const char* title, int x, int y, int w, int h, int flags);
      ~Window();

      SDL_Window* getSDL();
    private:
      SDL_Window* window;
    };
  };
};

#endif
