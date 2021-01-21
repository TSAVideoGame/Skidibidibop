#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_COLLISION_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_COLLISION_COMPONENT

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
       * Camera Component
       * ========================================
       */
      class CollisionManager : public Component
      {
      public:
        CollisionManager();
        ~CollisionManager();
        // All the data is stored in one buffer
        /*
         * Really offsets could be std::uint8_t but
         * there are some char problems with simple math
         * so will just go with std::uint16_t for now
         */
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          std::uint16_t* offset_x;
          std::uint16_t* offset_y;
          std::uint16_t* width;
          std::uint16_t* height;
        };

        // An instance of the component
        struct Instance
        {
          std::uint32_t index;
        };

        Instance get_instance(const Entity&);

        std::uint16_t  get_offset_x(Instance&);
        void           set_offset_x(Instance&, std::uint16_t);

        std::uint16_t  get_offset_y(Instance&);
        void           set_offset_y(Instance&, std::uint16_t);

        std::uint16_t  get_width(Instance&);
        void           set_width(Instance&, std::uint16_t);

        std::uint16_t  get_height(Instance&);
        void           set_height(Instance&, std::uint16_t);

        Instance add_component(const Entity&);
        void destroy_component(Instance&);
        // TODO: Destroy component when entity is destroyed
        Data data;
      private:
        // Given an entity id, this is how we will get the instance index
        std::unordered_map<Entity, std::uint32_t> map;

        void allocate(std::uint32_t);
      };
      
      // Register the transform component
      extern Manager::RegisterComponent<CollisionManager> collision_manager;
    };
  };
};

#endif
