#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_DIRECTION_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_DIRECTION_COMPONENT

#include "entity.h"
#include <cstdint>
#include <unordered_map>
#include "component.h"

namespace Game
{
  namespace ECS
  {
    namespace Components
    {
      /*
       * ========================================
       * Direction Component
       *
       * Has data related to direction
       * ========================================
       */
      class DirectionManager : public Component
      {
      public:
        DirectionManager();
        ~DirectionManager();
        // All the data is stored in one buffer
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          std::int8_t* direction;
        };

        // An instance of the component
        struct Instance
        {
          std::uint32_t index;
        };

        Instance get_instance(const Entity&);

        std::int8_t  get_direction(Instance&);
        void         set_direction(Entity&, std::int8_t);

        Instance add_component(const Entity&);
        void destroy_component(Instance&);
        // TODO: Destroy component when entity is destroyed
      private:
        Data data;
        // Given an entity id, this is how we will get the instance index
        std::unordered_map<Entity, std::uint32_t> map;

        void allocate(std::uint32_t);
      };

      // Register the transform component
      extern Manager::RegisterComponent<DirectionManager> direction_manager;
    };
  };
};

#endif
