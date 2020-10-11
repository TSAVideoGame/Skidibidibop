#ifndef SKIDIBIDIBOP_GAME_CORE_STATES
#define SKIDIBIDIBOP_GAME_CORE_STATES

/*
 * This setup for the game states are inspired by
 * how SDL_Events work
 */

namespace Game
{
  namespace Core
  {
    namespace States
    {
      enum class States {TITLE, GAME};

      struct Title
      {
      };

      struct Game
      {
        enum class States {NORMAL, PAUSED, CUTSCENE};
        States state;
      };

      struct State
      {
       States current;
       union
       {
         Title title;
         Game game;
       } data;
      };
    };
  };
};

#endif
