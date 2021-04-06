#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_PROJECTILE_DEF_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_PROJECTILE_DEF_COMPONENT

#include "entity.h"
#include <cstdint>
#include <unordered_map>
#include "component.h"
#include <vector>

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
			class ProjectileDefManager : public Component
			{
			public:
				ProjectileDefManager();
				~ProjectileDefManager();

        typedef void (*projectile_create_function)(Entity);
        typedef void (*projectile_function)();
        typedef void (*projectile_update_function)(int*, int*, int*, int*, int);

				// All the data is stored in one buffer
				struct Data
				{
					std::uint32_t instances; // Current instances
					std::uint32_t allocated; // Allocated instances
					void* buffer;

					Entity* entity;
					int* damage;
					int* status;
					float* bounce;
          projectile_create_function* on_create;
          projectile_update_function* on_update;
          projectile_function* on_destroy;
          int* max_ticks;
          int* flag;
				};

				// An instance of the component
				struct Instance
				{
					std::uint32_t index;
				};

				Instance get_instance(const Entity&);

        int  get_damage(Instance&);
        void set_damage(Instance&, int);

        int  get_status(Instance&);
        void set_status(Instance&, int);

        float get_bounce(Instance&);
        void  set_bounce(Instance&, float);

        projectile_create_function get_create(Instance&);
        void                       set_create(Instance&, projectile_create_function);

        projectile_update_function get_update(Instance&);
        void                       set_update(Instance&, projectile_update_function);

        projectile_function get_destroy(Instance&);
        void                set_destroy(Instance&, projectile_function);

        int  get_max_ticks(Instance&);
        void set_max_ticks(Instance&, int);

        int  get_flag(Instance&);
        void set_flag(Instance&, int);

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
			extern Manager::RegisterComponent<ProjectileDefManager> projectile_def_manager;
		};
	};
};

#endif
