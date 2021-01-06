#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_CAMERA_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_CAMERA_COMPONENT

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
      class CameraManager : public Component
      {
      public:
        CameraManager();
        ~CameraManager();
        // All the data is stored in one buffer
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          std::uint32_t* chunk;
          int* x;
          int* y;
        };

        // An instance of the component
        struct Instance
        {
          std::uint32_t index;
        };

        Instance get_instance(const Entity&);

        std::uint32_t get_chunk(Instance&);
        void          set_chunk(Instance&, std::uint32_t);

        int  get_x(Instance&);
        void set_x(Instance&, int);

        int  get_y(Instance&);
        void set_y(Instance&, int);

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
      extern Manager::RegisterComponent<CameraManager> camera_manager;
    };
  };
};

#endif
