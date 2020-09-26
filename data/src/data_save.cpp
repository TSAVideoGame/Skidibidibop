#include "data_save.h"
#include <fstream>

Data::Save::Data Data::Save::load(std::string& fpath)
{
  std::ifstream file(fpath, std::ios::binary);
  Data d = {Types::Map(file)};

  return d;
}

void Data::Save::save(Data data)
{

}
