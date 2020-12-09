#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_SYSTEM

#include <vector>
#include <stdexcept>

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
       * Singleton managing systems
       *
       * This works a little differently than
       * the plugin and component classes
       *
       * TODO: Order of updates/draws
       * ========================================
       */
      struct ManagerData
      {
      private:
        std::vector<void(*)()> update_functions;
        std::vector<void(*)()> draw_functions;

        std::size_t index = 0;
        std::vector<System*> systems;

        friend class Manager;
      };

      class Manager
      {
      public:
        static Manager& get_instance();

        void register_update(void(*)());
        void register_draw(void(*)());

        template <typename T> class RegisterSystem
        {
        public:
          RegisterSystem()
          {
            static_assert(std::is_base_of<System, T>::value, "System does not dervie from Game::ECS::Systems::System");
            Manager::get_instance().data.systems.push_back(new T());
          }
        };
      private:
        // TODO: Core should not create/delete manager
        Manager();
        ~Manager();

        void init();
        void close();

        void update();
        void draw();

        ManagerData data;

        friend class Game::Core;
      };
    };
  };
};

#endif
