#ifndef SKIDIBIDIBOP_EDITOR_TOOL_MAIN
#define SKIDIBIDIBOP_EDITOR_TOOL_MAIN

#include "tool.h"

namespace Editor
{
  namespace Tool
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
    };
  };
};

#endif
