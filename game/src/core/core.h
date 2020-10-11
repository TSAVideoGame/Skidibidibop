#ifndef SKIDIBIDIBOP_GAME_CORE_CORE
#define SKIDIBIDIBOP_GAME_CORE_CORE

#include "sdl.h"
#include "camera.h"
#include "core_states.h"
#include "core_manager_manager.h"
#include "core_inputs.h"

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

    // Using an enum rather than an enum class to make some of the math easier
    enum Directions {DIR_TOP, DIR_TOP_RIGHT, DIR_RIGHT, DIR_BOTTOM_RIGHT, DIR_BOTTOM, DIR_BOTTOM_LEFT, DIR_LEFT, DIR_TOP_LEFT};

    class Core
    {
    public:
      static void init();
      static void close();

      static void input();
      static void update();
      static void draw();

      static bool isRunning() { return running; }
      static States::State getState() { return state; }
      static Inputs::Pressed getInputs() { return inputs; }
      static SDL::Texture* const getTexture() { return texture; }

      static Game::Core::Camera camera;
    private:
      Core();

      static bool running;
      static States::State state;
      static Inputs::Pressed inputs;
      static SDL::Window* window;
      static SDL::Renderer* renderer;
      static SDL::Texture* texture;
      static ManagerManager* manager;
    };
  };
};

#endif
