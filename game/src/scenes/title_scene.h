#ifndef SKIDIBIDIBOP_GAME_SCENES_TITLE_SCENE
#define SKIDIBIDIBOP_GAME_SCENES_TITLE_SCENE

#include "scene.h"
#include "sdlw.h"

namespace Game
{
  namespace Scenes
  {
    class Title : public Scene
    {
    public:
      Title();
      ~Title();
      void update();
      void draw(SDLW::Renderer*);
    };

    extern Manager::RegisterScene<Title> title_scene;
  };
};

#endif
