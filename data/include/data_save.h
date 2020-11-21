#ifndef SKIDIBIDIBOP_DATA_SAVE
#define SKIDIBIDIBOP_DATA_SAVE

#include "data_types.h"
#include <string>

namespace Data
{
  /*
   * ========================================
   * Saves and loads the data
   *
   * Abstraction of Data::Types saving so
   * all data is saved/loaded in the correct
   * order
   *
   * I couldn't figure a better name so I'm
   * calling saving and loading save :(
   * ========================================
   */
  namespace Save
  {
    struct Data
    {
      Types::Map map;
      Types::Player player;
      Types::Inventory inventory;
      Types::Story story;
      Types::Bopdex bopdex;
      Types::Achievement achievement;
    };

    Data load(const std::string& fpath);
    void save(const std::string& fpath, Data&);
  };
};

#endif
