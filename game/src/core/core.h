#ifndef SKIDIBIDIBOP_GAME_CORE
#define SKIDIBIDIBOP_GAME_CORE

#include "sdlw.h"
#include <vector>
#include "plugin.h"
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

    // Plugin functions
    template<typename T> static T get_plugin()
    {
      static std::size_t index = add_plugin(new T());
      static_assert(std::is_base_of<Plugins::Plugin, T>::value, "Invalid plugin");
      return *(dynamic_cast<T*>(plugins[index]));
    }

    // Get / Set
    static bool is_running();
  private:
    // Unused methods
    Core();
    ~Core();

    // Plugin functions
    static void load_plugins();
    static void close_plugins();
    // The template uses this so I am defining it here as well
    static std::size_t add_plugin(Plugins::Plugin* p)
    {
      static std::size_t index = 0;
      plugins.push_back(p);
      return index++;
    }

    // Basic stuff
    static SDLW::Window* window;
    static SDLW::Renderer* renderer;
    static SDLW::Texture* spritesheet;
    static bool running;
    // Plugins
    static std::vector<Plugins::Plugin*> plugins;
  };
};

#endif
