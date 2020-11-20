#include "data_types.h"

/*
 * Room for improvement
 *
 * A boolean is stored as a byte when it only needs a bit
 */

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
      file.write(reinterpret_cast<char*>(&(*t).flag), sizeof(*t).flag);
      file.write(reinterpret_cast<char*>(&(*t).enemy_id), sizeof((*t).enemy_id));
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
      file.read(reinterpret_cast<char*>(&t.flag), sizeof(t.flag));
      file.read(reinterpret_cast<char*>(&t.enemy_id), sizeof(t.enemy_id));
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
  file.write(reinterpret_cast<char*>(&gender), sizeof(gender));
  file.write(reinterpret_cast<char*>(&health), sizeof(health));
  file.write(reinterpret_cast<char*>(&weapons.slot_a), sizeof(weapons.slot_a));
  file.write(reinterpret_cast<char*>(&weapons.slot_b), sizeof(weapons.slot_b));
  file.write(reinterpret_cast<char*>(&weapons.slot_current), sizeof(weapons.slot_current));
  file.write(reinterpret_cast<char*>(&level), sizeof(level));
  file.write(reinterpret_cast<char*>(&current_map), sizeof(current_map));
  file.write(reinterpret_cast<char*>(&position.x), sizeof(position.x));
  file.write(reinterpret_cast<char*>(&position.y), sizeof(position.y));
  file.write(reinterpret_cast<char*>(&direction), sizeof(direction));
  file.write(reinterpret_cast<char*>(&status), sizeof(status));
}

void Data::Types::Player::load(std::ifstream& file)
{
  file.read(reinterpret_cast<char*>(&gender), sizeof(gender));
  file.read(reinterpret_cast<char*>(&health), sizeof(health));
  file.read(reinterpret_cast<char*>(&weapons.slot_a), sizeof(weapons.slot_a));
  file.read(reinterpret_cast<char*>(&weapons.slot_b), sizeof(weapons.slot_b));
  file.read(reinterpret_cast<char*>(&weapons.slot_current), sizeof(weapons.slot_current));
  file.read(reinterpret_cast<char*>(&level), sizeof(level));
  file.read(reinterpret_cast<char*>(&current_map), sizeof(current_map));
  file.read(reinterpret_cast<char*>(&position.x), sizeof(position.x));
  file.read(reinterpret_cast<char*>(&position.y), sizeof(position.y));
  file.read(reinterpret_cast<char*>(&direction), sizeof(direction));
  file.read(reinterpret_cast<char*>(&status), sizeof(status));
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
  num_weapons = unlocked_weapons.size();
  file.write(reinterpret_cast<char*>(&num_weapons), sizeof(num_weapons));

  // A vector of bools get kinda funky, gotta use stream buffer iterators
  std::copy(unlocked_weapons.begin(), unlocked_weapons.end(), std::ostreambuf_iterator<char>(file));

  inventory_size = inventory.size();
  file.write(reinterpret_cast<char*>(&inventory_size), sizeof(inventory_size));

  for (std::vector<Item>::iterator i = inventory.begin(); i < inventory.end(); ++i)
  {
    file.write(reinterpret_cast<char*>(&(*i).id), sizeof((*i).id));
    file.write(reinterpret_cast<char*>(&(*i).slot), sizeof((*i).slot));
  }
}

void Data::Types::Inventory::load(std::ifstream& file)
{
  file.read(reinterpret_cast<char*>(&num_weapons), sizeof(num_weapons));
  unlocked_weapons.reserve(num_weapons);

  for (size_t i = 0; i < num_weapons; ++i)
  {
    bool data;
    file.read(reinterpret_cast<char*>(&data), sizeof(data));
    unlocked_weapons.push_back(data);
  }

  file.read(reinterpret_cast<char*>(&inventory_size), sizeof(inventory));
  inventory.reserve(inventory_size);

  for (size_t i = 0; i < inventory_size; ++i)
  {
    Item item;
    file.read(reinterpret_cast<char*>(&item.id), sizeof(item.id));
    file.read(reinterpret_cast<char*>(&item.slot), sizeof(item.slot));
    inventory.push_back(item);
  }
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
  num_quests = completed_quests.size();
  file.write(reinterpret_cast<char*>(&num_quests), sizeof(num_quests));

  std::copy(completed_quests.begin(), completed_quests.end(), std::ostreambuf_iterator<char>(file));
}

void Data::Types::Story::load(std::ifstream& file)
{
  file.read(reinterpret_cast<char*>(&num_quests), sizeof(num_quests));
  completed_quests.reserve(num_quests);

  for (size_t i = 0; i < num_quests; ++i)
  {
    bool data;
    file.read(reinterpret_cast<char*>(&data), sizeof(data));
    completed_quests.push_back(data);
  }
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
  num_entries = entries.size();
  file.write(reinterpret_cast<char*>(&num_entries), sizeof(num_entries));

  for (std::vector<Entry>::iterator i = entries.begin(); i < entries.end(); ++i)
  {
    file.write(reinterpret_cast<char*>(&(*i).viewed), sizeof((*i).viewed));
    file.write(reinterpret_cast<char*>(&(*i).defeated), sizeof((*i).defeated));
    file.write(reinterpret_cast<char*>(&(*i).num_viewed), sizeof((*i).num_viewed));
    file.write(reinterpret_cast<char*>(&(*i).num_defeated), sizeof((*i).num_defeated));
  }
}

void Data::Types::Bopdex::load(std::ifstream& file)
{
  file.read(reinterpret_cast<char*>(&num_entries), sizeof(num_entries));
  entries.reserve(num_entries);

  for (size_t i = 0; i < num_entries; ++i)
  {
    Entry entry;
    file.read(reinterpret_cast<char*>(&entry.viewed), sizeof(entry.viewed));
    file.read(reinterpret_cast<char*>(&entry.defeated), sizeof(entry.defeated));
    file.read(reinterpret_cast<char*>(&entry.num_viewed), sizeof(entry.num_viewed));
    file.read(reinterpret_cast<char*>(&entry.num_defeated), sizeof(entry.num_defeated));
    entries.push_back(entry);
  }
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

  num_achievements = completed_achievements.size();
  file.write(reinterpret_cast<char*>(&num_achievements), sizeof(num_achievements));

  std::copy(completed_achievements.begin(), completed_achievements.end(), std::ostreambuf_iterator<char>(file));
}

void Data::Types::Achievement::load(std::ifstream& file)
{

  file.read(reinterpret_cast<char*>(&num_achievements), sizeof(num_achievements));
  completed_achievements.reserve(num_achievements);

  for (size_t i = 0; i < num_achievements; ++i)
  {
    bool data;
    file.read(reinterpret_cast<char*>(&data), sizeof(data));
    completed_achievements.push_back(data);
  }
}

