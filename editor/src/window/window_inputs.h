#ifndef SKIDIBIDIBOP_EDITOR_WINDOW_INPUTS
#define SKIDIBIDIBOP_EDITOR_WINDOW_INPUTS

namespace Editor
{
  enum class MouseState {HOVER, CLICK, RELEASE, DRAG};
  struct Inputs
  {
    bool oldMouseDown, mouseDown;
    int clickMouseX, clickMouseY;
    int oldMouseX, oldMouseY;
    int mouseX, mouseY, mouseWheelY;
  };

};

#endif
