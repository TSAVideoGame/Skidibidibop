#ifndef SKIDIBIDIBOP_EDITOR_TOOL_MANAGER
#define SKIDIBIDIBOP_EDITOR_TOOL_MANAGER

#include "tool.h"
#include "window_inputs.h"
#include <vector>
#include <SDL2/SDL.h>

namespace Editor
{
  namespace Tool
  {
    class Manager
    {
    public:
      Manager(SDL_Renderer*);
      ~Manager();

      void update(MouseState, Inputs);
      void draw();

      SDL_Color getColor() { return selectedTab->getColor(); }
    private:
      std::vector<Tool::Tab*> tabs;
      Tool::Tab* selectedTab;
    };
  };
};

#endif
