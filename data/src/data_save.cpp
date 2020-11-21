#include "data_save.h"
#include <fstream>

Data::Save::Data Data::Save::load(const std::string& fpath)
{
  std::ifstream file(fpath, std::ios::binary);
  Data d = {
    Types::Map(file),
    Types::Player(file),
    Types::Inventory(file),
    Types::Story(file),
    Types::Bopdex(file),
    Types::Achievement(file)
  };

  return d;
}

/*
 * NOTE:
 * Be careful when passing in the file because it will get
 * completely re-written
 */
void Data::Save::save(const std::string& fpath, Data& data)
{
  std::ofstream file(fpath, std::ios::binary | std::ios::trunc);
  data.map.save(file);
  data.player.save(file);
  data.inventory.save(file);
  data.story.save(file);
  data.bopdex.save(file);
  data.achievement.save(file);
}
