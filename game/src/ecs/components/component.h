#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_COMPONENT

#include <vector>
#include <stdexcept>

#include <string>

namespace Game
{
  namespace ECS
  {
    namespace Components
    {
      /*
       * ========================================
       * 
       * This class has nothing because it's
       * simply for deriving components, which
       * I will need so I can register all the
       * components in the component manager
       * ========================================
       */
      class Component
      {
      public:
        virtual ~Component() {}
      };

      /*
       * ========================================
       * Components::Manager
       *
       * A singleton which holds all the components
       * ========================================
       */
      class Manager
      {
      public:
        static Manager& get_instance();

        template <typename T> class RegisterComponent
        {
        public:
          RegisterComponent()
          {
            Manager::get_instance().components.push_back(new T());
            Manager::get_instance().get_component<T>(); // This is needed to increment the index
          }
        };

        template <typename T> T* get_component()
        {
          static std::size_t i = index == components.size() - 1 ? index++ : throw std::logic_error("Unregistered component");
          return dynamic_cast<T*>(components[i]);
        }
      private:
        Manager();
        ~Manager();

        std::size_t index = 0;
        std::vector<Component*> components;
      };
    };
  };
};

#endif
