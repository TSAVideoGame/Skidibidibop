#include "data_types.h"

/*
 * ==========================================
 * Data::Types::Base
 * ==========================================
 */
Data::Types::Base::Base(Type type)
{
  this->type = type;
}

Data::Types::Base::~Base()
{

}

/*
 * ==========================================
 * Data::Types::Map
 * ==========================================
 */
Data::Types::Map::Map(std::ifstream& file) : Base(Type::MAP)
{
  load(file);
}

void Data::Types::Map::save(std::ofstream& file)
{
}

void Data::Types::Map::load(std::ifstream& file)
{
  // Load the size
  file.read(reinterpret_cast<char*>(&size.x), sizeof(size.x));
  file.read(reinterpret_cast<char*>(&size.y), sizeof(size.y));

  // Load the data
  tiles.reserve(size.x * size.y);

  for (size_t i = 0; i < size.x * size.y; i++)
  {
    Tile t;
    file.read(reinterpret_cast<char*>(&t.id), sizeof(t.id));
    file.read(reinterpret_cast<char*>(&t.Collision.top), sizeof(t.Collision.top));
    file.read(reinterpret_cast<char*>(&t.Collision.bottom), sizeof(t.Collision.bottom));
    file.read(reinterpret_cast<char*>(&t.Collision.left), sizeof(t.Collision.left));
    file.read(reinterpret_cast<char*>(&t.Collision.right), sizeof(t.Collision.right));
    file.read(reinterpret_cast<char*>(&t.state), sizeof(t.state));
    tiles.push_back(t);
  }
}
