#ifndef SKIDIBIDIBOP_GAME_PLUGINS_PLUGIN
#define SKIDIBIDIBOP_GAME_PLUGINS_PLUGIN

namespace Game
{
  // Core needs Plugins::Plugin, forward declaring here
  // to prevent circular dependencies
  class Core;

  namespace Plugins
  {
    class Plugin
    {
    protected:
      Plugin() {}
      virtual ~Plugin() {}

      friend class Game::Core; // Only core should create/delete plugins, IDK why I need full scope but getting errors without it
    };
  };
};

#endif
