#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_TAB
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_TAB

#include "sdlw.h"
#include <string>
#include <vector>
#include "window_inputs.h"

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      class Base;

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

        class Objects : public Tab
        {
        public:
          Objects(SDLW::Renderer*, int x, int y);
        };

        class Monsters : public Tab
        {
        public:
          Monsters(SDLW::Renderer*, int x, int y);
        };

        class NPCs : public Tab
        {
        public:
          NPCs(SDLW::Renderer*, int x, int y);
        };

        class Collisions : public Tab
        {
        public:
          Collisions(SDLW::Renderer*, int x, int y);
        };
      };
    };
  };
};

#endif
