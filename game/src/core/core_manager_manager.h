#ifndef SKIDIBIDIBOP_GAME_CORE_Manager_MANAGER
#define SKIDIBIDIBOP_GAME_CORE_MANAGER_MANAGER

#include "core_object_manager.h"
#include "sdlw.h"

namespace Game
{
  namespace Core
  {
    /*
     * ========================================
     * Manages all the object managers
     * ========================================
     */
    class ManagerManager : public Object::Manager
    {
    public:
      ManagerManager(SDLW::Renderer*);
      void update();
    private:
      std::deque<Object::Base*> activeObjects;
    };
  };
};

#endif
