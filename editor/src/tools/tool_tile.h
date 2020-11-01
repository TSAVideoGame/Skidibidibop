#ifndef SKIDIBIDIBOP_EDITOR_TOOL_TILE
#define SKIDIBIDIBOP_EDITOR_TOOL_TILE

#include "tool.h"

namespace Editor
{
  namespace Tool
  {
    namespace Tile
    {
      class Col : public Base
      {
      public:
        Col(SDLW::Renderer*, int x, int y);
        ~Col();

        void update(MouseState);
        void draw();
      private:
        SDLW::Texture* numberTexs[10];
      };

      class Row : public Base
      {
      public:
        Row(SDLW::Renderer*, int x, int y);
        ~Row();

        void update(MouseState);
        void draw();
      private:
        SDLW::Texture* numberTexs[10];
      };
    };
  };
};

#endif
