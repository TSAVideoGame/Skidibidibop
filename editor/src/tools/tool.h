#ifndef SKIDIBIDIBOP_EDITOR_TOOL
#define SKIDIBIDIBOP_EDITOR_TOOL

#include <SDL2/SDL.h>
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

      Base(const std::string&, int x, int y);
      virtual ~Base();

      virtual void update(MouseState, Inputs) = 0;
      virtual void draw();

      bool selected;
    protected:
      std::string text;
      SDL_Texture* texture;
    };

    // Tabs organize tools
    class Tab
    {
    public:
      Tab(SDL_Renderer*, const std::string&, int x, int y, SDL_Color);
      ~Tab();

      void update(MouseState);
      void draw();

      bool isHovered(int mx, int my);

      SDL_Color getColor() { return color; }
    private:
      int x, y;
      SDL_Color color;
      std::string text;
      SDL_Texture* texture;
      std::vector<Base*> tools;
      SDL_Renderer* renderer;
    };
  };
};

#endif
