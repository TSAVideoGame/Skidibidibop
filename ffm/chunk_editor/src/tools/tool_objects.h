#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_OBJECTS
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_OBJECTS

#include "tool.h"

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      namespace Objects
      {
        class Edit : public Base
        {
        public:
          Edit(SDLW::Renderer*, int x, int y);
        };

        class Images : public Base
        {
        public:
          Images(SDLW::Renderer*, int x, int y);
          void update(MouseState);
          void draw();
        private:
          int page; // Which page of sprites it's on
          int selected_id; // Which sprite is selected
        };
      };
    };
  };
};

#endif
