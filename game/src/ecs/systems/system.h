#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_SYSTEM

#include "sdlw.h"
#include <vector>
#include <stdexcept>

namespace Game
{
  class Core;

  namespace ECS
  {
    namespace Systems
    {
      /*
       * ========================================
       * System
       *
       * There aren't even update and draw methods
       * here, that's because a system can do
       * whatever it wants basically, as long as
       * it's main goal is 'manipulating' the data
       * ========================================
       */
      class System
      {
      public:
        virtual ~System() {}
      protected:
        // Only Systems::Manager will initialize systems
        // TODO: This doesn't work
        System() {}

        friend class Manager;
      };

      /*
       * ========================================
       * Systems::Manager
       *
       * Singleton managing systems
       *
       * At first systems don't really need a manager,
       * because scenes manage systems, but this system
       * manager will manage the instances of a system
       * ========================================
       */
      class Manager
      {
      public:
        static Manager& get_instance();

        template <typename T> class RegisterSystem
        {
        public:
          RegisterSystem()
          {
            static_assert(std::is_base_of<System, T>::value, "System does not dervie from Game::ECS::Systems::System");
            Manager::get_instance().systems.push_back(new T());
            Manager::get_instance().get_system<T>();
          }
        };

        template <typename T> T* get_system()
        {
          static std::size_t i = index == systems.size() - 1 ?  index++ : throw std::logic_error("Unregistered System");

          return dynamic_cast<T*>(systems[i]);
        }
      private:
        Manager();
        ~Manager();

        std::size_t index = 0;
        std::vector<System*> systems;
      };
    };
  };
};

#endif
