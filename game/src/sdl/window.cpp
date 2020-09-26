#include "window.h"

Game::SDL::Window::Window(const char* title, int x, int y, int w, int h, int flags)
{
  window = SDL_CreateWindow(title, x, y, w, h, flags);
}

Game::SDL::Window::~Window()
{
  SDL_DestroyWindow(window);
}

SDL_Window* Game::SDL::Window::getSDL()
{
  return window;
}
