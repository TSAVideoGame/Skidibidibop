#include "sdlw_window.h"

SDLW::Window::Window(const char* title, int x, int y, int w, int h, int flags)
{
  window = SDL_CreateWindow(title, x, y, w, h, flags);
}

SDLW::Window::~Window()
{
  SDL_DestroyWindow(window);
}

SDL_Window* SDLW::Window::get_SDL()
{
  return window;
}
