#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_SYSTEM

#include <vector>

namespace Game
{
  class Core;

  namespace ECS
  {
    namespace Systems
    {
      class System
      {
      public:
        virtual ~System() {}
        // TODO: register functions should only be called by Systems::Manager, but it needs to be inherited
        virtual void register_functions() {}
      };

      /*
       * ========================================
       * Systems::Manager
       *
       * This works a little differently than
       * the plugin and component classes
       * ========================================
       */
      struct ManagerData
      {
      private:
        std::vector<void(*)()> update_functions;
        std::vector<void(*)()> draw_functions;
        std::vector<System*> systems;

        friend class Manager;
      };

      class Manager
      {
      public:
        static void register_system(System*);
        static void register_update(void(*)());
        static void register_draw(void(*)());
      private:
        static void init();
        static void close();

        static void update();
        static void draw();

        static ManagerData data;

        friend class Game::Core;
      };
    };
  };
};

#endif
