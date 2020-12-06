#ifndef SKIDIBIDIBOP_GAME_PLUGINS_PLUGIN
#define SKIDIBIDIBOP_GAME_PLUGINS_PLUGIN

#include <vector>

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
          Manager::get_instance().get_plugin<T>();
        }
      };

      // TODO: This will mess up if you get a plugin which isn't registered
      template <typename T> T* get_plugin()
      {
        static std::size_t index = plugins.size() - 1;
        return dynamic_cast<T*>(plugins[index]);
      }
    private:
      Manager();
      ~Manager();

      static std::vector<Plugin*> plugins; 
    };
  };
};

#endif
