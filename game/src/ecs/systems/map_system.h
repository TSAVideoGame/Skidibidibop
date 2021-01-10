#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_MAP_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_MAP_SYSTEM

#include "system.h"
#include "sdlw.h"
#include "ffm_data.h"
#include <vector>

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
        static void update();
        static void draw(SDLW::Renderer*);
        static std::uint32_t get_top_left_chunk();
      private:
        static std::vector<FFM::Data::Types::Chunk> chunks;
        static std::uint32_t top_left_chunk;
        static std::vector<SDLW::Texture*> chunk_textures;
      };

      extern Manager::RegisterSystem<Map> map_system;
    };
  };
};

#endif
