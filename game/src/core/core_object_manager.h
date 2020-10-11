#ifndef SKIDIBIDIBOP_GAME_CORE_OBJECT_MANAGER
#define SKIDIBIDIBOP_GAME_CORE_OBJECT_MANAGER

#include "core_object.h"
#include <deque>

namespace Game
{
  namespace Core
  {
    namespace Object
    {
      /*
       * ========================================
       * Game::Core::Object::Manager
       *
       * Manages objects of a type
       * ========================================
       */
      class Manager : public Base
      {
      public:
        Manager();
        virtual ~Manager();
        virtual void update();
        virtual void draw();
      protected:
        std::deque<Base*> objects;
        void empty();
      };
    };
  };
};

#endif
