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
      static const int WIDTH = 64, HEIGHT = 32;

      Base(SDLW::Renderer*, const std::string&, int x, int y);
      virtual ~Base();

      virtual void update(MouseState) = 0;
      virtual void draw();

      bool selected;
    protected:
      SDLW::Renderer* renderer;
      std::string text;
      int x, y;
      SDL_Rect destRect;
      SDLW::Texture* texture;
    };

    class Numeric : public Base
    {
    public:
      Numeric(SDLW::Renderer*, const std::string&, int x, int y, unsigned int min, unsigned int max, unsigned int* variable);
      virtual ~Numeric();

      virtual void draw();
    protected:
      unsigned int min, max;
      unsigned int* variable;
      bool hover_increment();
      bool hover_decrement();
      SDLW::Texture* number_textures[10];
    };

    class Checkbox : public Base
    {
    public:
      Checkbox(SDLW::Renderer*, const std::string&, int x, int y, bool* variable);
      virtual ~Checkbox();

      virtual void draw();
    protected:
      bool* variable;
      bool hover();
    };
  };
};

#endif
