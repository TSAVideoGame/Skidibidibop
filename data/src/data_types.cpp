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
  // Write the number of sections
  num_sections = sections.size();
  file.write(reinterpret_cast<char*>(&num_sections), sizeof(num_sections));

  // Write all the sections
  for (std::vector<Section>::iterator i = sections.begin(); i < sections.end(); ++i)
  {
    // Write the section size
    file.write(reinterpret_cast<char*>(&(*i).size.x), sizeof((*i).size.x));
    file.write(reinterpret_cast<char*>(&(*i).size.y), sizeof((*i).size.y));

    // Write the tile data
    for (std::vector<Tile>::iterator t = (*i).tiles.begin(); t < (*i).tiles.end(); ++i)
    {
      file.write(reinterpret_cast<char*>(&(*t).id), sizeof((*t).id));
      file.write(reinterpret_cast<char*>(&(*t).collision.top), sizeof((*t).collision.top));
      file.write(reinterpret_cast<char*>(&(*t).collision.bottom), sizeof((*t).collision.bottom));
      file.write(reinterpret_cast<char*>(&(*t).collision.left), sizeof((*t).collision.left));
      file.write(reinterpret_cast<char*>(&(*t).collision.right), sizeof((*t).collision.right));
      file.write(reinterpret_cast<char*>(&(*t).state), sizeof((*t).state));
    }
  }
}

void Data::Types::Map::load(std::ifstream& file)
{
  // Load the amount of sections
  file.read(reinterpret_cast<char*>(&num_sections), sizeof(num_sections));

  // Reserve size for sections
  sections.reserve(num_sections);

  // Fill up sections with section data
  for (size_t i = 0; i < num_sections; ++i)
  {
    Section s;
    // Load the amount of tiles
    file.read(reinterpret_cast<char*>(&s.size.x), sizeof(s.size.x));
    file.read(reinterpret_cast<char*>(&s.size.y), sizeof(s.size.y));

    // Reserve size for tiles
    s.tiles.reserve(s.size.x * s.size.y);

    // Load up the tiles
    for (size_t i = 0; i < s.size.x * s.size.y; ++i)
    {
      Tile t;
      file.read(reinterpret_cast<char*>(&t.id), sizeof(t.id));
      file.read(reinterpret_cast<char*>(&t.collision.top), sizeof(t.collision.top));
      file.read(reinterpret_cast<char*>(&t.collision.bottom), sizeof(t.collision.bottom));
      file.read(reinterpret_cast<char*>(&t.collision.left), sizeof(t.collision.left));
      file.read(reinterpret_cast<char*>(&t.collision.right), sizeof(t.collision.right));
      file.read(reinterpret_cast<char*>(&t.state), sizeof(t.state));
      s.tiles.push_back(t);
    }

    sections.push_back(s);
  }
}

/*
 * ==========================================
 * Data::Types::Player
 * ==========================================
 */
Data::Types::Player::Player(std::ifstream& file) : Base(Type::MAP)
{
  load(file);
}

void Data::Types::Player::save(std::ofstream& file)
{

}

void Data::Types::Player::load(std::ifstream& file)
{

}

/*
 * ==========================================
 * Data::Types::Inventory
 * ==========================================
 */
Data::Types::Inventory::Inventory(std::ifstream& file) : Base(Type::MAP)
{
  load(file);
}

void Data::Types::Inventory::save(std::ofstream& file)
{

}

void Data::Types::Inventory::load(std::ifstream& file)
{

}

/*
 * ==========================================
 * Data::Types::Story
 * ==========================================
 */
Data::Types::Story::Story(std::ifstream& file) : Base(Type::MAP)
{
  load(file);
}

void Data::Types::Story::save(std::ofstream& file)
{

}

void Data::Types::Story::load(std::ifstream& file)
{

}

/*
 * ==========================================
 * Data::Types::Bopdex
 * ==========================================
 */
Data::Types::Bopdex::Bopdex(std::ifstream& file) : Base(Type::MAP)
{
  load(file);
}

void Data::Types::Bopdex::save(std::ofstream& file)
{

}

void Data::Types::Bopdex::load(std::ifstream& file)
{

}

/*
 * ==========================================
 * Data::Types::Achievement
 * ==========================================
 */
Data::Types::Achievement::Achievement(std::ifstream& file) : Base(Type::MAP)
{
  load(file);
}

void Data::Types::Achievement::save(std::ofstream& file)
{

}

void Data::Types::Achievement::load(std::ifstream& file)
{

}

