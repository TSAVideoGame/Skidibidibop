#ifndef SKIDIBIDIBOP_GAME_CORE_CORE
#define SKIDIBIDIBOP_GAME_CORE_CORE

#include "sdl.h"

namespace Game
{
  namespace Core
  {
    class Core
    {
    public:
      static void init();
      static void close();

      static void input();
      static void update();
      static void draw();

      static bool isRunning() { return running; }
    private:
      Core();

      static bool running;
      static SDL::Window* window;
    };

    enum class State {TITLE, GAME};
  };
};

#endif
