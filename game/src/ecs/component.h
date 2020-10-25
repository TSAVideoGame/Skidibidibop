#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENT

#include <algorithm>

namespace Game
{
  namespace ECS
  {
    class Component;
    class Entity;

    size_t getComponentTypeID()
    {
      static size_t lastID = 0;
      return lastID++;
    }

    template <typename T> size_t getComponentTypeID()
    {
      static size_t typeID = getComponentTypeID();
      return typeID;
    }
  };
};

#endif
