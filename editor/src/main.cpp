#include "window.h"
#include <SDL2/SDL_ttf.h>

int main(int argc, char* args[])
{
  Editor::Window::init();

  while (Editor::Window::isRunning())
  {
    Editor::Window::input();
    Editor::Window::draw();
    Editor::Window::update();
  }

  Editor::Window::close();

  return 0;
}
