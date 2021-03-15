#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_LINE_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_LINE_COMPONENT

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
      class LineManager : public Component
      {
      public:
        LineManager();
        ~LineManager();
        // All the data is stored in one buffer
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          std::uint32_t* v1_x;
          std::uint32_t* v1_y;
          std::uint32_t* v2_x;
          std::uint32_t* v2_y;
        };

        // An instance of the component
        struct Instance
        {
          std::uint32_t index;
        };

        Instance get_instance(const Entity&);

        std::uint32_t get_v1_x(Instance&);
        void          set_v1_x(Instance&, std::uint32_t);

        std::uint32_t get_v1_y(Instance&);
        void          set_v1_y(Instance&, std::uint32_t);

        std::uint32_t get_v2_x(Instance&);
        void          set_v2_x(Instance&, std::uint32_t);

        std::uint32_t get_v2_y(Instance&);
        void          set_v2_y(Instance&, std::uint32_t);

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
      extern Manager::RegisterComponent<LineManager> line_manager;
    };
  };
};

#endif
