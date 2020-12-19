#ifndef SKIDIBIDIBOP_GAME_SCENES_TEST_SCENE
#define SKIDIBIDIBOP_GAME_SCENES_TEST_SCENE

#include "scene.h"

namespace Game
{
  namespace Scenes
  {
    class TestScene : public Scene
    {
    public:
      TestScene();
      ~TestScene();
      void update();
      void draw(SDLW::Renderer*);
    };

    extern Manager::RegisterScene<TestScene> testScene;
  };
};

#endif
