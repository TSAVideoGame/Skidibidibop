#ifndef SKIDIBIDIBOP_EDITOR_WINDOW
#define SKIDIBIDIBOP_EDITOR_WINDOW

#include "sdlw.h"
#include "window_inputs.h"
#include "tool_manager.h"
#include "data.h"
#include <string>

namespace Editor
{
  namespace Tool
  {
    class Manager;
  }

  class Window
  {
  public:
    static void init();
    static void close();

    static void input();
    static void update();
    static void draw();

    static void setCurrentFile(const std::string&);

    static bool isRunning();
    static Inputs getInputs();
    static std::string getCurrentFile();
    // Data is going to be manipulated so might as well be public
    static Data::Save::Data data;
  private:
    Window();
    ~Window();

    static bool running;
    static SDLW::Window* window;
    static SDLW::Renderer* renderer;
    static Inputs inputs;
    static Tool::Manager* toolManager;
    static std::string currentFile;
    static SDLW::Texture* currentFileTex;
  };
};

#endif
