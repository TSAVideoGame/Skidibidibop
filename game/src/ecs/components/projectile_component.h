#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_PROJECTILE_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_PROJECTILE_COMPONENT

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
       * Projectile Component
       *
       * Has data related to Projectile
       * ========================================
       */
      class ProjectileManager : public Component
      {
      public:
        ProjectileManager();
        ~ProjectileManager();
        // All the data is stored in one buffer
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          int* x;
          int* y;
          int* w;
          int* h;
          int* direction;
          int* ticks;
          Entity* projectile_def;
        };

        // An instance of the component
        struct Instance
        {
          std::uint32_t index;
        };

        Instance get_instance(const Entity&);

        int  get_x(Instance&);
        void set_x(Instance&, int);

        int  get_y(Instance&);
        void set_y(Instance&, int);

        int  get_w(Instance&);
        void set_w(Instance&, int);

        int  get_h(Instance&);
        void set_h(Instance&, int);

        int  get_direction(Instance&);
        void set_direction(Instance&, int);

        int  get_ticks(Instance&);
        void set_ticks(Instance&, int);

        Entity get_projectile_def(Instance&);
        void   set_projectile_def(Instance&, Entity);

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
      extern Manager::RegisterComponent<ProjectileManager> projectile_manager;
    };
  };
};

#endif
