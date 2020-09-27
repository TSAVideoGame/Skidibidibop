#ifndef SKIDIBIDIBOP_GAME_CORE_CORE
#define SKIDIBIDIBOP_GAME_CORE_CORE

#include "sdl.h"

namespace Game
{
  namespace Core
  {
    struct
    {
      struct
      {
        int WIDTH = 960;
        int HEIGHT = 640;
      } WINDOW;
    } CONSTANTS;

    enum class State {TITLE, GAME};

    class Core
    {
    public:
      static void init();
      static void close();

      static void input();
      static void update();
      static void draw();

      static bool isRunning() { return running; }
      static State getState() { return state; }
      static SDL::Texture* const getTexture() { return texture; }
    private:
      Core();

      static bool running;
      static State state;
      static SDL::Window* window;
      static SDL::Renderer* renderer;
      static SDL::Texture* texture;
    };
  };
};

#endif
