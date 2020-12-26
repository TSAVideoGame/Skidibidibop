#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_MONSTERS
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_MONSTERS

#include "tool.h"
#include <vector>

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      namespace Monsters
      {
        namespace Edit
        {
          class Main : public Base
          {
          public:
            Main(SDLW::Renderer*, int x, int y);
            ~Main();

            void update(MouseState);
            void draw();

            Base* selected_tool;
            int selected_monster; // The index of it
          private:
            std::vector<Base*> tools;
            
          };

          class Id : public Numeric<std::uint16_t>
          {
          public:
            Id(SDLW::Renderer*, int x, int y);

            void update(MouseState);
          };

          class Delete : public Base
          {
          public:
            Delete(SDLW::Renderer*, int x, int y);

            void update(MouseState);
          private:
            bool is_selected;
          };
        };

        class Add : public Base
        {
        public:
          Add(SDLW::Renderer*, int x, int y);

          void update(MouseState);
          void draw();
        };
      };
    };
  };
};

#endif
