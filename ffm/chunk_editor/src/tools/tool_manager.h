#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_MANAGER
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL_MANAGER

#include "tool_tab.h"
#include "window_inputs.h"
#include <vector>
#include "sdlw.h"

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      /*
       * ========================================
       * Tools::Manager
       *
       * Manages tabs, not tools
       * ========================================
       */
      class Manager
      {
      public:
        Manager(SDLW::Renderer*);
        ~Manager();

        void update(MouseState);
        void draw();

        SDL_Color get_color() { return selected_tab->get_color(); }
      private:
        std::vector<Tools::Tab*> tabs;
        Tools::Tab* selected_tab;
      };
    };
  };
};

#endif
