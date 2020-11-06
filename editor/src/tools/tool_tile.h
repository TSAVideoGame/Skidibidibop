#ifndef SKIDIBIDIBOP_EDITOR_TOOL_TILE
#define SKIDIBIDIBOP_EDITOR_TOOL_TILE

#include "tool.h"
#include <vector>
#include "data.h"

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

      namespace Edit
      {
        // Row and Col tools will deselect this if needed
        class Main : public Base
        {
        public:
          Main(SDLW::Renderer*, int x, int y);
          ~Main();

          void update(MouseState);
          void draw();

          Data::Types::Map::Tile* selectedTile = nullptr;
        private:
          std::vector<Base*> tools;
          SDL_Rect selectedTileRect;
        };

        class ID : public Base
        {
        public:
          ID(SDLW::Renderer*, int x, int y);
          ~ID();

          void update(MouseState);
          void draw();
        private:
          SDLW::Texture* numberTexs[10];
        };

        class TopCollision : public Base
        {
        public:
          TopCollision(SDLW::Renderer*, int x, int y);
          ~TopCollision();

          void update(MouseState);
          void draw();
        };

        class RightCollision : public Base
        {
        public:
          RightCollision(SDLW::Renderer*, int x, int y);
          ~RightCollision();

          void update(MouseState);
          void draw();
        };

        class BottomCollision : public Base
        {
        public:
          BottomCollision(SDLW::Renderer*, int x, int y);
          ~BottomCollision();

          void update(MouseState);
          void draw();
        };

        class LeftCollision : public Base
        {
        public:
          LeftCollision(SDLW::Renderer*, int x, int y);
          ~LeftCollision();

          void update(MouseState);
          void draw();
        };
      };
    };
  };
};

#endif
