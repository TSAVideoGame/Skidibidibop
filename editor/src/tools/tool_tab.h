#ifndef SKIDIBIDIBOP_EDITOR_TOOL_TAB
#define SKIDIBIDIBOP_EDITOR_TOOL_TAB

#include "tool.h"
#include "sdlw.h"

namespace Editor
{
  namespace Tool
  {
    // Tabs organize tools
    class Tab
    {
    public:
      Tab(SDLW::Renderer*, const std::string&, int x, int y, SDL_Color);
      ~Tab();

      void update(MouseState);
      void draw();

      bool isHovered(int mx, int my);
      SDL_Color getColor() { return color; }

      // Don't have time to bother making this properly, just gonna be public for now
      bool isSelected;
    protected:
      int x, y;
      SDL_Rect dest_rect;
      SDL_Color color;
      std::string text;
      SDLW::Texture* texture;
      std::vector<Base*> tools;
      SDLW::Renderer* renderer;
    };

    // Tabs has tabs with pre-added tools
    namespace Tabs
    {
      class Main : public Tab
      {
      public:
        Main(SDLW::Renderer*, const std::string&, int x, int y, SDL_Color);
      };

      class Tile : public Tab
      {
      public:
        Tile(SDLW::Renderer*, const std::string&, int x, int y, SDL_Color);
      };
    };
  };
};

#endif
