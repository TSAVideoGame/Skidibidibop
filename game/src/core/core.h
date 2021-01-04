#ifndef SKIDIBIDIBOP_GAME_CORE
#define SKIDIBIDIBOP_GAME_CORE

#include "sdlw.h"
#include <vector>
#include <cstdint>
#include "input.h"
#include "logger.h"
#include "ffm_data.h"
#include <fstream>

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
    static const Input::Data get_inputs();
    // Logger
    static Logger logger;
    // Temporary
    static SDLW::Texture* get_texture() { return spritesheet; }
    // Resources (Temporary)
    static std::ifstream map_file;
    static FFM::Data::Types::Map map_helper;
  private:
    // Unused methods
    Core();
    ~Core();

    // Basic stuff
    static SDLW::Window* window;
    static SDLW::Renderer* renderer;
    static bool running;
    // Input
    static Input::Data inputs;
    static Input::KeyBindings key_bindings;
    // Resources
    static SDLW::Texture* spritesheet;
  };
};

#endif
