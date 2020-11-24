#include "data_types.h"
#include <cmath>

// There are 5 mystery bytes after a tile, that's probably causing the headaches

/*
 * Room for improvement
 *
 * There is gonna be a maximum of 7 bits wasted but I can't bother with that
 */
static void write_bools(std::ofstream& file, const std::vector<bool>& v, size_t amount)
{
  for (size_t i = 0; i < amount; i += 8)
  {
    uint8_t data = 0;

    for (int j = 0; j < 8; ++j)
    {
      if (v[i + j])
      {
        data |= 1 << j;
      }
    }

    file.write(reinterpret_cast<char*>(&data), sizeof(data));
  }
}

static std::vector<bool> read_bools(std::ifstream& file, size_t amount)
{
  std::vector<bool> v;
  v.reserve(amount);

  for (size_t i = 0; i < std::ceil(amount / 8.0); i += 8)
  {
    uint8_t data = 0;
    file.read(reinterpret_cast<char*>(&data), sizeof(data));

    for (int j = 0; j < 8; ++j)
    {
      // Make sure extra bits aren't read, there is possibility of padding
      if (j + i >= amount)
        break;

      v.push_back((data >> j) & 1);
    }
  }

  return v;
}

static bool check_file(std::ifstream& file)
{
  if (file.eof())
  {
    throw std::runtime_error("Data::BAD_FILE: reached EOF early");
    return false;
  }

  return true;
}

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
Data::Types::Map::Map() : Base(Type::MAP)
{
  num_sections = 0;  
}

Data::Types::Map::Map(std::ifstream& file) : Base(Type::MAP)
{
  Map();
  load(file);
}

#include <iostream>
void Data::Types::Map::save(std::ofstream& file)
{
  // Write the number of sections
  num_sections = sections.size();
  file.write(reinterpret_cast<char*>(&num_sections), sizeof(num_sections));

  std::cout << "Saving " << num_sections << " sections" << std::endl;

  // Write all the sections
  if (num_sections > 0)
  {
    for (std::vector<Section>::iterator s = sections.begin(); s < sections.end(); ++s)
    {
      // Write the section size
      file.write(reinterpret_cast<char*>(&(*s).size.x), sizeof((*s).size.x));
      file.write(reinterpret_cast<char*>(&(*s).size.y), sizeof((*s).size.y));

      std::cout << "Saving " << (*s).size.x * (*s).size.y << " tiles" << std::endl;

      // Write the tile data
      for (std::vector<Tile>::iterator t = (*s).tiles.begin(); t < (*s).tiles.end(); ++t)
      {
        file.write(reinterpret_cast<char*>(&(*t).id), sizeof((*t).id));
        file.write(reinterpret_cast<char*>(&(*t).collision.top), sizeof((*t).collision.top));
        file.write(reinterpret_cast<char*>(&(*t).collision.right), sizeof((*t).collision.right));
        file.write(reinterpret_cast<char*>(&(*t).collision.bottom), sizeof((*t).collision.bottom));
        file.write(reinterpret_cast<char*>(&(*t).collision.left), sizeof((*t).collision.left));
        file.write(reinterpret_cast<char*>(&(*t).state), sizeof((*t).state));
        file.write(reinterpret_cast<char*>(&(*t).flag), sizeof(*t).flag);
        file.write(reinterpret_cast<char*>(&(*t).enemy_id), sizeof((*t).enemy_id));
      }
    }
  }
}

void Data::Types::Map::load(std::ifstream& file)
{
  check_file(file);
  // Load the amount of sections
  file.read(reinterpret_cast<char*>(&num_sections), sizeof(num_sections));

  std::cout << "Loading " << num_sections << " sections" << std::endl;

  // Reserve size for sections
  sections.reserve(num_sections);

  // Fill up sections with section data
  for (size_t si = 0; si < num_sections; ++si)
  {
    Section s;
    // Load the amount of tiles
    file.read(reinterpret_cast<char*>(&s.size.x), sizeof(s.size.x));
    file.read(reinterpret_cast<char*>(&s.size.y), sizeof(s.size.y));

    // Reserve size for tiles
    s.tiles.reserve(s.size.x * s.size.y);

    std::cout << "Loading " << s.size.x * s.size.y << " tiles" << std::endl;

    // Load up the tiles
    for (size_t ti = 0; ti < s.size.x * s.size.y; ++ti)
    {
      Tile t;
      file.read(reinterpret_cast<char*>(&t.id), sizeof(t.id));
      file.read(reinterpret_cast<char*>(&t.collision.top), sizeof(t.collision.top));
      file.read(reinterpret_cast<char*>(&t.collision.right), sizeof(t.collision.right));
      file.read(reinterpret_cast<char*>(&t.collision.bottom), sizeof(t.collision.bottom));
      file.read(reinterpret_cast<char*>(&t.collision.left), sizeof(t.collision.left));
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
Data::Types::Player::Player() : Base(Type::PLAYER)
{
  gender = true;
  health = 2;
  weapons = {0, 0, 0};
  level = 0;
  current_map = 0;
  position = {0, 0};
  direction = 2;
  status = 2;
}

Data::Types::Player::Player(std::ifstream& file) : Base(Type::PLAYER)
{
  Player();
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
  check_file(file);

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
Data::Types::Inventory::Inventory() : Base(Type::INVENTORY)
{
  num_weapons = 0;
  inventory_size = 0;
}

Data::Types::Inventory::Inventory(std::ifstream& file) : Base(Type::INVENTORY)
{
  Inventory();
  load(file);
}

void Data::Types::Inventory::save(std::ofstream& file)
{
  num_weapons = unlocked_weapons.size();
  file.write(reinterpret_cast<char*>(&num_weapons), sizeof(num_weapons));

  std::cout << "Saving " << num_weapons << " weapons" << std::endl;

  if (num_weapons > 0) // Only save it if there is stuff to save
  {
    write_bools(file, unlocked_weapons, num_weapons);
  }

  inventory_size = inventory.size();
  file.write(reinterpret_cast<char*>(&inventory_size), sizeof(inventory_size));

  std::cout << "Saving " << inventory_size << " items" << std::endl;

  for (std::vector<Item>::iterator i = inventory.begin(); i < inventory.end(); ++i)
  {
    file.write(reinterpret_cast<char*>(&(*i).id), sizeof((*i).id));
    file.write(reinterpret_cast<char*>(&(*i).slot), sizeof((*i).slot));
  }
}

void Data::Types::Inventory::load(std::ifstream& file)
{
  check_file(file);

  file.read(reinterpret_cast<char*>(&num_weapons), sizeof(num_weapons));

  std::cout << "Loading " << num_weapons << " weapons" << std::endl;

  unlocked_weapons = read_bools(file, num_weapons);

  file.read(reinterpret_cast<char*>(&inventory_size), sizeof(inventory));
  inventory.reserve(inventory_size);

  std::cout << "Loading " << inventory_size << " items" << std::endl;

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
Data::Types::Story::Story() : Base(Type::STORY),
  completed_quests()
{
  num_quests = 0;
}

Data::Types::Story::Story(std::ifstream& file) : Base(Type::STORY)
{
  Story();
  load(file);
}

void Data::Types::Story::save(std::ofstream& file)
{
  num_quests = completed_quests.size();
  file.write(reinterpret_cast<char*>(&num_quests), sizeof(num_quests));

  std::cout << "Saving " << num_quests << " quests" << std::endl;

  write_bools(file, completed_quests, num_quests);
}

void Data::Types::Story::load(std::ifstream& file)
{
  check_file(file);

  file.read(reinterpret_cast<char*>(&num_quests), sizeof(num_quests));

  std::cout << "Loading " << num_quests << " quests" << std::endl;

  completed_quests = read_bools(file, num_quests);
}

/*
 * ==========================================
 * Data::Types::Bopdex
 * ==========================================
 */
Data::Types::Bopdex::Bopdex() : Base(Type::BOPDEX),
  entries()
{
  num_entries = 0;
}

Data::Types::Bopdex::Bopdex(std::ifstream& file) : Base(Type::BOPDEX)
{
  Bopdex();
  load(file);
}

void Data::Types::Bopdex::save(std::ofstream& file)
{
  num_entries = entries.size();
  file.write(reinterpret_cast<char*>(&num_entries), sizeof(num_entries));

  std::cout << "Saving " << num_entries << " entires" << std::endl;

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
  check_file(file);

  file.read(reinterpret_cast<char*>(&num_entries), sizeof(num_entries));
  entries.reserve(num_entries);

  std::cout << "Loading " << num_entries << " entires" << std::endl;

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
Data::Types::Achievement::Achievement() : Base(Type::ACHIEVEMENT),
  completed_achievements()
{
  num_achievements = 0;
}

Data::Types::Achievement::Achievement(std::ifstream& file) : Base(Type::ACHIEVEMENT)
{
  Achievement();
  load(file);
}

void Data::Types::Achievement::save(std::ofstream& file)
{
  num_achievements = completed_achievements.size();
  file.write(reinterpret_cast<char*>(&num_achievements), sizeof(num_achievements));

  std::cout << "Saving " << num_achievements << " achievements" << std::endl;

  write_bools(file, completed_achievements, num_achievements);
}

void Data::Types::Achievement::load(std::ifstream& file)
{
  check_file(file);

  file.read(reinterpret_cast<char*>(&num_achievements), sizeof(num_achievements));

  std::cout << "Loading " << num_achievements << " achievements" << std::endl;

  completed_achievements = read_bools(file, num_achievements);
}

