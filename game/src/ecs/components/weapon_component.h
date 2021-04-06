#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_WEAPON_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_WEAPON_COMPONENT

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
       * Weapon Component
       *
       * Has data related to direction
       * ========================================
       */
      class WeaponManager : public Component
      {
      public:
        WeaponManager();
        ~WeaponManager();
        // All the data is stored in one buffer
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          std::uint16_t* id;
          int* cooldown;
          std::uint32_t* animation_id;
          std::uint32_t* projectile_id;
        };

        // An instance of the component
        struct Instance
        {
          std::uint32_t index;
        };

        Instance get_instance(const Entity&);
        Instance get_instance(std::uint16_t);

        std::uint16_t get_id(Instance&);
        void          set_id(Instance&, std::uint16_t);

        int  get_cooldown(Instance&);
        void set_cooldown(Instance&, int);

        std::uint32_t get_animation_id(Instance&);
        void           set_animation_id(Instance&, std::uint32_t);

        std::uint32_t get_projectile_id(Instance&);
        void           set_projectile_id(Instance&, std::uint32_t);

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
      extern Manager::RegisterComponent<WeaponManager> weapon_manager;
    };
  };
};

#endif