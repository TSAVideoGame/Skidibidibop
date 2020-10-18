#ifndef SKIDIBIDIBOP_EDITOR_WINDOW
#define SKIDIBIDIBOP_EDITOR_WINDOW

#include "sdlw.h"
#include "window_inputs.h"
#include "tool_manager.h"

namespace Editor
{
  namespace Tool
  {
    class Manager;
  }

  class Window
  {
  public:
    Window();
    ~Window();

    void input();
    void update();
    void draw();

    void save();

    bool isRunning() { return running; }
    Inputs getInputs() { return inputs; }
  private:
    bool running;
    SDLW::Window* window;
    SDLW::Renderer* renderer;
    Inputs inputs;
    Tool::Manager* toolManager;
  };
};

#endif
