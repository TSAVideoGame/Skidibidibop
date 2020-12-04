#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_TRANSFORM_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_TRANSFORM_COMPONENT

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
       * Transform Component
       *
       * Has data related to position
       * ========================================
       */
      class TransformManager : public Component
      {
      public:
        TransformManager();
        ~TransformManager();
        // All the data is stored in one buffer
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          std::uint16_t* tile_x;
          std::uint16_t* tile_y;
          int* offset_x;
          int* offset_y;
        };

        // An instance of the component
        struct Instance
        {
          std::uint32_t index;
        };

        Instance get_instance(Entity&);
        std::uint16_t get_tile_x(Instance&);
        std::uint16_t get_tile_y(Instance&);
        int get_offset_x(Instance&);
        int get_offset_y(Instance&);

        Instance add_component(Entity&);
        void destroy_component(Instance&);
      private:
        Data data;
        // Given an entity id, this is how we will get the instance index
        std::unordered_map<Entity, std::uint32_t> map;

        void allocate(std::uint32_t);
      };
    };
  };
};

#endif
