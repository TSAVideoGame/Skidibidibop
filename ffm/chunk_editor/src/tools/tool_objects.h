#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_OBJECTS
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_OBJECTS

#include "tool.h"
#include <vector>

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      namespace Objects
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
            int selected_object; // The index of it
          private:
            std::vector<Base*> tools;
            
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

        class Images : public Numeric<std::uint16_t>
        {
        public:
          Images(SDLW::Renderer*, int x, int y);

          void update(MouseState);
          void draw();
        private:
          std::uint16_t page; // Which page of sprites it's on
          const int PAGE_AMOUNT = 10; // How many sprites per page
          int selected_id; // Which sprite is selected
          SDLW::Texture* number_textures[10];
        };
      };
    };
  };
};

#endif
