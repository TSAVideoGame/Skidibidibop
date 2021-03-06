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
  // Temporary, should be an entity/component thingy
  struct Camera 
  {
    int x, y;
  };

  enum class GameState {NORMAL, MENU, SETTINGS, MAP, CUTSCENE};

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
    static GameState get_state();
    // Logger
    static Logger logger;
    // If an update() needs the renderer it can get it via this, not final though
    static SDLW::Renderer* renderer;
    // Temporary
    static SDLW::Texture* get_texture() { return spritesheet; }
    // Resources (Temporary)
    static std::ifstream map_file;
    static FFM::Data::Types::Map map_helper;
    static Camera camera;
    static std::uint32_t current_chunk;
  private:
    // Unused methods
    Core();
    ~Core();

    // Basic stuff
    static SDLW::Window* window;
    static bool running;
    // Input
    static Input::Data inputs;
    static Input::KeyBindings key_bindings;
    // Game State
    static GameState game_state;
    // Resources
    static SDLW::Texture* spritesheet;
  };
};

#endif
