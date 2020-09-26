#ifndef SKIDIBIDIBOP_DATA_TYPES
#define SKIDIBIDIBOP_DATA_TYPES

#include <fstream>
#include <vector>

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
    enum class Type {MAP, PLAYER};
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

    class Map : public Base
    {
    public:
      Map(std::ifstream&);

      void save(std::ofstream&);
      void load(std::ifstream&);

      struct Size
      {
        unsigned int x, y;
      };

      struct Tile
      {
        unsigned int id;
        struct
        {
          bool top, bottom, left, right;
        } Collision;
        unsigned int state;
      };

      Size size;
      std::vector<Tile> tiles;
    };

    // Later add a player one
  };
};

#endif
