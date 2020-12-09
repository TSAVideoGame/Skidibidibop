#ifndef SKIDIBIDIBOP_GAME_PLUGINS_PLUGIN
#define SKIDIBIDIBOP_GAME_PLUGINS_PLUGIN

#include <vector>
#include <stdexcept>

namespace Game
{
  // Core needs Plugins::Plugin, forward declaring here
  // to prevent circular dependencies
  class Core;

  namespace Plugins
  {
    class Plugin
    {
    public:
      virtual ~Plugin() {}
    };

    /*
     * ========================================
     * Plugins::Manager
     *
     * A singleton which manages all the plugins
     * ========================================
     */
    class Manager
    {
    public:
      static Manager& get_instance();

      template <typename T> class RegisterPlugin
      {
      public:
        RegisterPlugin()
        {
          static_assert(std::is_base_of<Plugin, T>::value, "Plugin does not derive from Game::Plugins::Plugin");
          Manager::get_instance().plugins.push_back(new T());
        }
      };

      template <typename T> T* get_plugin()
      {
        static std::size_t i = index == plugins.size() - 1 ? index++ : throw std::logic_error("Getting unregistered plugin");
        return dynamic_cast<T*>(plugins[i]);
      }
    private:
      Manager();
      ~Manager();

      std::size_t index = 0; // Plugin index, needed for the get_plugin function
      std::vector<Plugin*> plugins; 
    };
  };
};

#endif
