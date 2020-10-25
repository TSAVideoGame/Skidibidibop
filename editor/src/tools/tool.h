#ifndef SKIDIBIDIBOP_EDITOR_TOOL
#define SKIDIBIDIBOP_EDITOR_TOOL

#include "sdlw.h"
#include "window_inputs.h"
#include "constants.h"
#include <string>
#include <vector>

namespace Editor
{
  namespace Tool
  {
    // Base tool, which is something that does some editing to the data
    class Base
    {
    public:
      static const int WIDTH = 2 * Constants::Grid.size, HEIGHT = Constants::Grid.size;

      Base(SDLW::Renderer*, const std::string&, int x, int y);
      virtual ~Base();

      virtual void update(MouseState, Inputs) = 0;
      virtual void draw();

      bool selected;
    protected:
      SDLW::Renderer* renderer;
      std::string text;
      int x, y;
      SDL_Rect destRect;
      SDLW::Texture* texture;
    };

  };
};

#endif
