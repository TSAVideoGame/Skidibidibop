#ifndef SKIDIBIDIBOP_GAME_OBJECT
#define SKIDIBIDIBOP_GAME_OBJECT

#include "sdlw.h"

namespace Game
{
  namespace Core
  {
    namespace Object
    {
      class Base
      {
      public:
        virtual ~Base();
        virtual void update() = 0;
        virtual void draw() = 0;
      };

      /*
       * ========================================
       * Game::Core::Object::Object
       *
       * An object which is drawn to the screen
       * ========================================
       */
      class Object : public Base
      {
      public:
        Object(SDLW::Renderer*);
        virtual ~Object();
        virtual void update() = 0;
        void draw();
      protected:
        SDL_Rect srcRect;
        SDL_Rect destRect;
        SDLW::Renderer* renderer;
      };
    };
  };
};

#endif
