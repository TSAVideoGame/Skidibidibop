#ifndef SKIDIBIDIBOP_EDITOR_TOOL_MANAGER
#define SKIDIBIDIBOP_EDITOR_TOOL_MANAGER

#include "tool_tab.h"
#include "window_inputs.h"
#include <vector>
#include "sdlw.h"

namespace Editor
{
  namespace Tool
  {
    class Manager
    {
    public:
      Manager(SDLW::Renderer*);
      ~Manager();

      void update(MouseState);
      void draw();

      SDL_Color getColor() { return selectedTab->getColor(); }
    private:
      std::vector<Tool::Tab*> tabs;
      Tool::Tab* selectedTab;
    };
  };
};

#endif
