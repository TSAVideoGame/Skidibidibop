#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_TAB
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_TAB

#include "sdlw.h"
#include <string>
#include "tool.h"
#include <vector>

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      class Tab
      {
      public:
        Tab(SDLW::Renderer*, const std::string&, int x, int y, SDL_Color);
        ~Tab();

        void update(MouseState);
        void draw();

        bool is_hovered(int mx, int my);
        SDL_Color get_color() { return color; }

        bool is_selected;
      protected:
        int x, y;
        SDL_Rect dest_rect;
        SDL_Color color;
        std::string text;
        SDLW::Texture* texture;
        std::vector<Base*> tools;
        SDLW::Renderer* renderer;
      };

      // Prefilled with tools
      namespace Tabs
      {
        class Main : public Tab
        {
        public:
          Main(SDLW::Renderer*, int x, int y);
        };
      };
    };
  };
};

#endif
