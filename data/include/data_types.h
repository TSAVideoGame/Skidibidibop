#ifndef SKIDIBIDIBOP_DATA_TYPES
#define SKIDIBIDIBOP_DATA_TYPES

#include <fstream>
#include <vector>

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
        unsigned int x, y;
      };

      struct Tile
      {
        struct Collision
        {
          bool top, bottom, left, right;
        };
        unsigned int id;
        Collision collision;
        unsigned int state;
        unsigned int flag;
        unsigned int enemy_id; // The enemy on the tile
      };

      // A section is a part of the map which gets loaded, a house is a different section from the main world
      struct Section
      {
        Size size;
        std::vector<Tile> tiles;
      };

      unsigned int num_sections;
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
        unsigned int slot_a, slot_b;
        unsigned char slot_current;
      };

      struct Position
      {
        unsigned int x, y;
      };

      bool gender;
      unsigned int health;
      Weapons weapons;
      unsigned int level;
      unsigned int current_map;
      Position position;
      unsigned char direction;
      unsigned int status;
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
        unsigned int id;
        unsigned int slot;
      };

      unsigned int num_weapons;
      std::vector<bool> unlocked_weapons;

      unsigned int inventory_size;
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

      unsigned int num_quests;
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
        unsigned int num_viewed;
        unsigned int num_defeated;
      };

      unsigned int num_entries;
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

      unsigned int num_achievements;
      std::vector<bool> completed_achievements;
    };
  };
};

#endif
