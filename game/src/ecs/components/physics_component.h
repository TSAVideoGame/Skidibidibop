#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_PHYSICS_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_PHYSICS_COMPONENT

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
       * Physics Component
       *
       * Has data related to movement
       * - Velocities (vel)
       * - Acceleration (accel)
       * ========================================
       */
      class PhysicsManager : public Component
      {
      public:
        PhysicsManager();
        ~PhysicsManager();
        // All the data is stored in one buffer
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          float* x_vel;
          float* y_vel;
          float* x_accel;
          float* y_accel;
          float* max_x_vel;
          float* max_y_vel;
        };

        // An instance of the component
        struct Instance
        {
          std::uint32_t index;
        };

        Instance get_instance(const Entity&);

        float get_x_vel(Instance&);
        void  set_x_vel(Instance&, float);

        float get_y_vel(Instance&);
        void  set_y_vel(Instance&, float);

        float get_x_accel(Instance&);
        void  set_x_accel(Instance&, float);

        float get_y_accel(Instance&);
        void  set_y_accel(Instance&, float);

        float get_max_x_vel(Instance&);
        void  set_max_x_vel(Instance&, float);

        float get_max_y_vel(Instance&);
        void  set_max_y_vel(Instance&, float);

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
      extern Manager::RegisterComponent<PhysicsManager> physics_manager;
    };
  };
};

#endif
