#ifndef SKIDIBIDIBOP_EDITOR_WINDOW
#define SKIDIBIDIBOP_EDITOR_WINDOW

#include "sdlw.h"
#include "window_inputs.h"
#include "tool_manager.h"
#include "data.h"
#include <string>
#include "tool.h"

namespace Editor
{
  namespace Tool
  {
    class Manager;
  }

  class Window
  {
  public:
    static void init();
    static void close();

    static void input();
    static void update();
    static void draw();

    static void set_current_file(const std::string&);

    static bool is_running();
    static Inputs get_inputs();
    static std::string get_current_file();
    static size_t get_first_tile();
    static std::uint16_t get_current_section();
    static void set_current_section(std::uint16_t);
    static unsigned int get_current_zoom();
    // Data is going to be manipulated so might as well be public
    static Data::Save::Data data;
    static Tool::Base* selected_tool;
  private:
    Window();
    ~Window();

    static void draw_tiles();
    static size_t firstTile; // Top-left most tile
    static void update_current_file();
    static void create_current_file_texture();
    static void update_current_section();

    static bool running;
    static SDLW::Window* window;
    static SDLW::Renderer* renderer;
    static Inputs inputs;
    static Tool::Manager* tool_manager;
    static std::string current_file;
    static std::string queue_file;
    static std::uint16_t current_section;
    static std::uint16_t queue_section;
    static unsigned int current_zoom;
    static SDLW::Texture* current_file_tex;
    static SDLW::Texture* spritesheet;
  };
};

#endif
