#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_SYSTEM

#include <vector>

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class System
      {
      public:
        virtual ~System();
      };

      class Manager
      {
      public:
        Manager();
        ~Manager();

        void update();
        void draw();

        void register_update(void(*)());
        void register_draw(void(*)());
      private:
        std::vector<void(*)()> update_functions;
        std::vector<void(*)()> draw_functions;
      };
    };
  };
};

#endif
