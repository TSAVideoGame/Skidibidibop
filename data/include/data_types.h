#ifndef SKIDIBIDIBOP_DATA_TYPES
#define SKIDIBIDIBOP_DATA_TYPES

#include <fstream>
#include <vector>
#include <cstdint>

/*
 * NOTE:
 * All the save methods should be const but I don't want
 * to deal with const qualifying all the casts right now
 * so they won't be const as of now
 */

namespace Data
{
  /*
   * ========================================
   * Data::Types
   *
   * The types used to deal with opening/loading
   * data.
   * ========================================
   */
  namespace Types
  {
    enum class Type {MAP, PLAYER, INVENTORY, STORY, BOPDEX, ACHIEVEMENT};
    /*
     * ========================================
     * Data::Types::Base
     *
     * The base data type
     * ========================================
     */
    class Base
    {
    public:
      virtual ~Base();

      virtual void save(std::ofstream&) = 0;
      virtual void load(std::ifstream&) = 0;
    protected:
      Base(Type);
      Type type;
    };

    /*
     * ========================================
     * Data::Types::Map
     *
     * Map data
     * ========================================
     */
    class Map : public Base
    {
    public:
      Map();
      Map(std::ifstream&);

      void save(std::ofstream&);
      void load(std::ifstream&);

      struct Size
      {
        std::uint16_t x, y;
      };

      struct Tile
      {
        struct Collision
        {
          bool top, right, bottom, left;
        };
        std::uint16_t id;
        Collision collision;
        std::uint16_t state;
        std::uint16_t flag;
        std::uint16_t enemy_id; // The enemy on the tile
      };

      // A section is a part of the map which gets loaded, a house is a different section from the main world
      struct Section
      {
        Size size;
        std::vector<Tile> tiles;
      };

      std::uint16_t num_sections;
      std::vector<Section> sections;
    };

    /*
     * ========================================
     * Data::Types::Player
     *
     * Player data, but not player stats
     * ========================================
     */
    class Player : public Base
    {
    public:
      Player();
      Player(std::ifstream&);

      void save(std::ofstream&);
      void load(std::ifstream&);

      struct Weapons
      {
        std::uint16_t slot_a, slot_b;
        std::uint8_t slot_current;
      };

      struct Position
      {
        std::uint16_t x, y;
      };

      bool gender;
      std::uint16_t health;
      Weapons weapons;
      std::uint8_t level;
      std::uint16_t current_map;
      Position position;
      std::uint8_t direction;
      std::uint16_t status;
    };

    /*
     * ========================================
     * Data::Types::Inventory
     *
     * Inventory data (weapons and items)
     * ========================================
     */
    class Inventory : public Base
    {
    public:
      Inventory();
      Inventory(std::ifstream&);

      void save(std::ofstream&);
      void load(std::ifstream&);


      struct Item
      {
        std::uint16_t id;
        std::uint16_t slot;
      };

      std::uint16_t num_weapons;
      std::vector<bool> unlocked_weapons;

      std::uint16_t inventory_size;
      std::vector<Item> inventory;
    };

    /*
     * ========================================
     * Data::Types::Story
     *
     * Story data
     * ========================================
     */
    class Story : public Base
    {
    public:
      Story();
      Story(std::ifstream&);

      void save(std::ofstream&);
      void load(std::ifstream&);

      std::uint16_t num_quests;
      std::vector<bool> completed_quests;
    };

    /*
     * ========================================
     * Data::Types::Bopdex
     *
     * Bopdex data
     * ========================================
     */
    class Bopdex : public Base
    {
    public:
      Bopdex();
      Bopdex(std::ifstream&);

      void save(std::ofstream&);
      void load(std::ifstream&);

      struct Entry
      {
        bool viewed;
        bool defeated;
        std::uint16_t num_viewed;
        std::uint16_t num_defeated;
      };

      std::uint16_t num_entries;
      std::vector<Entry> entries;
    };

    /*
     * ========================================
     * Data::Types::Achievements
     *
     * Achievments data
     * NOTE: We are not sure if we're going to use this,
     *       but better to have it just in case
     * ========================================
     */
    class Achievement : public Base
    {
    public:
      Achievement();
      Achievement(std::ifstream&);

      void save(std::ofstream&);
      void load(std::ifstream&);

      std::uint16_t num_achievements;
      std::vector<bool> completed_achievements;
    };
  };
};

#endif
