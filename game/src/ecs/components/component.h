#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_COMPONENT

#include <vector>
#include <deque>

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

      class Manager
      {
      public:
        Manager();
        ~Manager();

        template<typename T> T* get_component()
        {
          static std::size_t index = add_component(new T());
          static_assert(std::is_base_of<Component, T>::value, "Invalid component");
          return dynamic_cast<T*>(components[index]);
        }
      private:
        std::vector<Component*> components;

        std::size_t add_component(Component* c)
        {
          static std::size_t index = 0;
          components.push_back(c);
          return index++;
        }
      };
    };
  };
};

#endif
