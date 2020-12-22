#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_WINDOW
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_WINDOW

#include "sdlw.h"
#include "window_inputs.h"
#include "ffm_data.h"
#include "tool_manager.h"

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      class Base;
    };

    class Window
    {
    public:
      static void init();
      static void close();

      static void input();
      static void update();
      static void draw();

      static void update_background();

      static bool is_running();
      static Inputs get_inputs();

      // Is going to manipulated anyways so will just be public
      static Data::Types::Chunk data;
      static Tools::Base* selected_tool; 
    private:
      Window();
      ~Window();

      static bool running;
      static SDLW::Window* window;
      static SDLW::Renderer* renderer;
      static SDLW::Texture* spritesheet;
      static SDLW::Texture* background;
      static Inputs inputs;

      static Tools::Manager* tool_manager;
    };
  };
};

#endif
