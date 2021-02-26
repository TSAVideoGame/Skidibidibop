#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_MAP_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_MAP_SYSTEM

#include "system.h"
#include "sdlw.h"
#include "ffm_data.h"
#include "entity.h"
#include <vector>
#include <deque>

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      // TODO: System inits and quits to clean resources,
      class Map : public System
      {
      public:
        void init();
        void quit();
        static void update();
        static void draw(SDLW::Renderer*);
        static std::uint32_t get_current_chunk();
      private:
        static std::vector<FFM::Data::Types::Chunk> chunks;
        static std::uint32_t current_chunk; // Top left chunk
        static SDLW::Texture* chunk_textures[9];

        static std::deque<std::deque<Entity>> chunk_entities;

        static void update_music();
        static void load_stuff(int chunk_index);
      };

      extern Manager::RegisterSystem<Map> map_system;
    };
  };
};

#endif
