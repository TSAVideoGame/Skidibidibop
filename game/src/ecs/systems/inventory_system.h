#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_INVENTORY_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_INVENTORY_SYSTEM

#include "system.h"
#include "sdlw.h"
#include <cstdint>
#include <vector>

namespace Game
{
	namespace ECS
	{
		namespace Systems
		{
			class Inventory : public System
			{
			public:
        void init();
				static void update();
				static std::uint16_t slots[];
        static std::uint8_t slot_selected;
				static std::vector<std::uint16_t> weapons;
			};

			extern Manager::RegisterSystem<Inventory> inventory_system;
		};
	};
};

#endif
