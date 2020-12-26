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
      static SDLW::Texture* get_spritesheet();

      // Is going to manipulated anyways so will just be public
      // This is pretty messy
      // Long story short, code wasn't planned beforehand
      static std::uint32_t background_id;
      static std::uint16_t music_id;
      static std::uint16_t x, y;
      static std::vector<Data::Types::Chunk::Object> objects;
      static std::vector<Data::Types::Chunk::Vertex> object_vertices;
      static std::vector<Data::Types::Chunk::Enemy> monsters;
      static std::vector<Data::Types::Chunk::Vertex> monster_vertices;
      static std::vector<Data::Types::Chunk::NPC> npcs;
      static std::vector<Data::Types::Chunk::Vertex> npc_vertices;
      static std::vector<Data::Types::Chunk::Line> lines;
      static std::vector<Data::Types::Chunk::Vertex> line_vertices;

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
