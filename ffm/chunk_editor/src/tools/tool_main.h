#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_MAIN
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_MAIN

#include "tool.h"

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      namespace Main
      {
        class Save : public Base
        {
        public:
          Save(SDLW::Renderer*, int x, int y);

          void update(MouseState);
        };

        class Load : public Base
        {
        public:
          Load(SDLW::Renderer*, int x, int y);

          void update(MouseState);
        };

        class Background : public Numeric<std::uint32_t>
        {
        public:
          Background(SDLW::Renderer*, int x, int y);
          void update(MouseState);
        private:
          std::uint32_t prev_id;
        };

        class PosX : public Numeric<std::uint16_t>
        {
        public:
          PosX(SDLW::Renderer*, int x, int y);
        };

        class PosY : public Numeric<std::uint16_t>
        {
        public:
          PosY(SDLW::Renderer*, int x, int y);
        };
      };
    };
  };
};

#endif
