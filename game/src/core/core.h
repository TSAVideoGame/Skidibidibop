#ifndef SKIDIBIDIBOP_GAME_CORE_CORE
#define SKIDIBIDIBOP_GAME_CORE_CORE

namespace Game
{
  namespace Core
  {
    class Core
    {
    public:
      static void init();
      static void close();

      static void input();
      static void update();
      static void draw();
    private:
      Core();
    };

    enum class State {TITLE, GAME};
  };
};

#endif
