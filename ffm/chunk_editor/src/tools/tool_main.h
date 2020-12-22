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

        class PosX : public Numeric
        {
        public:
          PosX(SDLW::Renderer*, int x, int y);

          void update(MouseState);
        };

        class PosY : public Numeric
        {
        public:
          PosY(SDLW::Renderer*, int x, int y);

          void update(MouseState);
        };
      };
    };
  };
};

#endif
