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
      class Col : public Numeric
      {
      public:
        Col(SDLW::Renderer*, int x, int y);
        ~Col();

        void update(MouseState);
      };

      class Row : public Numeric
      {
      public:
        Row(SDLW::Renderer*, int x, int y);
        ~Row();

        void update(MouseState);
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

          Data::Types::Map::Tile* selected_tile = nullptr;
        private:
          std::vector<Base*> tools;
          size_t selected_tile_num;
        };

        class ID : public Numeric
        {
        public:
          ID(SDLW::Renderer*, int x, int y, int min, int max, std::uint16_t* variable);
          ~ID();

          void update(MouseState);
        };

        // TODO: Make a collision namespace for these
        class TopCollision : public Checkbox
        {
        public:
          TopCollision(SDLW::Renderer*, int x, int y, bool* variable);
          ~TopCollision();

          void update(MouseState);
        };

        class RightCollision : public Checkbox
        {
        public:
          RightCollision(SDLW::Renderer*, int x, int y, bool* variable);
          ~RightCollision();

          void update(MouseState);
        };

        class BottomCollision : public Checkbox
        {
        public:
          BottomCollision(SDLW::Renderer*, int x, int y, bool* variable);
          ~BottomCollision();

          void update(MouseState);
        };

        class LeftCollision : public Checkbox
        {
        public:
          LeftCollision(SDLW::Renderer*, int x, int y, bool* variable);
          ~LeftCollision();

          void update(MouseState);
        };

        class State : public Numeric
        {
        public:
          State(SDLW::Renderer*, int x, int y, int min, int max, std::uint16_t* variable);
          ~State();

          void update(MouseState);
        };

        class Flag : public Numeric
        {
        public:
          Flag(SDLW::Renderer*, int x, int y, int min, int max, std::uint16_t* variable);
          ~Flag();

          void update(MouseState);
        };

        class Monster : public Numeric
        {
        public:
          Monster(SDLW::Renderer*, int x, int y, int min, int max, std::uint16_t* variable);
          ~Monster();

          void update(MouseState);
        };
      };
    };
  };
};

#endif
