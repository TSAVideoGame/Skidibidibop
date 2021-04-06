#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_PROJECTILE_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_PROJECTILE_SYSTEM

#include "system.h"
#include "sdlw.h"

namespace Game
{
	namespace ECS
	{
		namespace Systems
		{
			class Projectile : public System
			{
			public:
				static void update();
			};

			extern Manager::RegisterSystem<Projectile> projectile_system;
		};
	};
};

#endif
