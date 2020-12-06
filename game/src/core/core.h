#ifndef SKIDIBIDIBOP_GAME_CORE
#define SKIDIBIDIBOP_GAME_CORE

#include "sdlw.h"
#include <vector>
#include <cstdint>

namespace Game
{
  class Core
  {
  public:
    static void init();
    static void close();

    static void input();
    static void update();
    static void draw();

    // Get / Set
    static bool is_running();
  private:
    // Unused methods
    Core();
    ~Core();

    // Basic stuff
    static SDLW::Window* window;
    static SDLW::Renderer* renderer;
    static SDLW::Texture* spritesheet;
    static bool running;
  };
};

#endif
