#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_COLLISIONS
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_COLLISIONS

#include "tool.h"

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      namespace Collisions
      {
        namespace Vertex
        {
          class Add : public Base
          {
          public:
            Add(SDLW::Renderer*, int x, int y);

            void update(MouseState);
            void draw();
          };

          class Remove : public Base
          {
          public:
            Remove(SDLW::Renderer*, int x, int y);

            void update(MouseState);
          };
        };

        namespace Line
        {
          class Add : public Base
          {
          public:
            Add(SDLW::Renderer*, int x, int y);

            void update(MouseState);
          private:
            int v1;
            // We don't need to store the 2nd vertex
          };

          class Remove : public Base
          {
          public:
            Remove(SDLW::Renderer*, int x, int y);

            void update(MouseState);
          };
        };

        class Clear : public Base
        {
        public:
          Clear(SDLW::Renderer*, int x, int y);

          void update(MouseState);
        };
      };
    };
  };
};

#endif
