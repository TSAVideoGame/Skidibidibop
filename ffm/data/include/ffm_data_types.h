#ifndef SKIDIBIDIBOP_FFM_DATA_TYPES
#define SKIDIBIDIBOP_FFM_DATA_TYPES

#include <fstream>
#include <cstdint>
#include <vector>

namespace FFM
{
  namespace Data
  {
    namespace Types
    {
      class Base
      {
      public:
        virtual ~Base() {}

        virtual void save(std::ofstream&) = 0;
        virtual void load(std::ifstream&) = 0;
      };

      class Chunk : public Base
      {
      public:
        Chunk();
        Chunk(std::ifstream&);

        void save(std::ofstream&);
        void load(std::ifstream&);

        // Remove stray vertices, pack the vectors
        void clean();

        struct Vertex
        {
          std::uint16_t x, y;
        };

        struct Line
        {
          // Index of the vertices
          std::uint16_t vertex_1;
          std::uint16_t vertex_2;
          std::uint16_t flag; // Special Collisions
        };

        struct Object
        {
          std::uint16_t vertex;
          std::uint16_t id;
        };

        struct Enemy
        {
          std::uint16_t vertex;
          std::uint16_t id;
        };

        struct NPC
        {
          std::uint16_t vertex;
          std::uint16_t id;
        };


        std::uint32_t size; // Size in bytes
        std::uint16_t x, y; // The chunk's (x,y) relative to the map
        std::uint32_t background_id;
        std::uint16_t music_id;

        std::uint16_t num_vertices;
        std::vector<Vertex> vertices;
        std::uint16_t num_lines;
        std::vector<Line> lines;
        std::uint16_t num_objects;
        std::vector<Object> objects;
        std::uint16_t num_enemies;
        std::vector<Enemy> enemies;
        std::uint16_t num_npcs;
        std::vector<NPC> npcs;
      };

      /*
       * ========================================
       * Map Data
       *
       * To access chunks use the sizes vector
       * along with the .ffmf file
       * ========================================
       */
      class Map : public Base
      {
      public:
        Map();
        Map(std::ifstream&);

        void save(std::ofstream&);
        void load(std::ifstream&);

        std::uint16_t x, y;
        std::uint32_t num_chunks;
        std::vector<std::uint32_t> sizes;
      };
    };
  };
};

#endif
