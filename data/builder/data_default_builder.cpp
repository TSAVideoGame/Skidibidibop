#include "data_default_builder.h"
#include "data_save.h"
#include <iostream>
#include <fstream>

/*
 * =========================================
 * Data::DefaultBuilder::build
 *
 * Builds a default sbbd data file, allows
 * some customizations:
 *
 * - Map section dimensions for one section
 * =========================================
 */
void Data::DefaultBuilder::build()
{
  Save::Data data = {
    Types::Map(),
    Types::Player(),
    Types::Inventory(),
    Types::Story(),
    Types::Bopdex(),
    Types::Achievement()
  };

  // Map stuff
  data.map.num_sections = 1;
  data.map.sections.push_back(Types::Map::Section());

  std::cout << "Enter the map dimensions (unsigned integers >= 1):\n";
  std::cin >> data.map.sections[0].size.x;
  std::cin >> data.map.sections[0].size.y;

  for (size_t i = 0; i < data.map.sections[0].size.x * data.map.sections[0].size.y; ++i)
  {
    data.map.sections[0].tiles.push_back({0, {false, false, false, false}, 0, 0, 0});
  }

  Save::save("default.sbbd", data);

  std::cout << "default.sbbd created" << std::endl;
}
