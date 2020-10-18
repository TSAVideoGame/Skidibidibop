#include "window.h"
#include "constants.h"

Editor::Window::Window()
{
  window = new SDLW::Window("SBB Editor", 64, 64, Constants::Window.width, Constants::Window.height, 0);
  renderer = new SDLW::Renderer(window);
  inputs = {false, false, 0, 0, 0, 0, 0, 0, 0};
  running = true;
  toolManager = new Tool::Manager(renderer);
}

Editor::Window::~Window()
{
  delete toolManager;
  delete renderer;
  delete window;
}

void Editor::Window::input()
{
  inputs.oldMouseDown = inputs.mouseDown;
  inputs.oldMouseX = inputs.mouseX;
  inputs.oldMouseY = inputs.mouseY;
  inputs.mouseWheelY = 0;

  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
      {
        running = false;
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
      {
        switch (e.button.button)
        {
          case SDL_BUTTON_LEFT:
          {
            inputs.mouseDown = true;
            if (!inputs.oldMouseDown)
              SDL_GetMouseState(&inputs.clickMouseX, &inputs.clickMouseY);
            break;
          }
        }
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        switch (e.button.button)
        {
          case SDL_BUTTON_LEFT:
          {
            inputs.mouseDown = false;
            break;
          }
        }
        break;
      }
      case SDL_MOUSEWHEEL:
      {
        inputs.mouseWheelY = e.wheel.y;
        break;
      }
    }
  }

  SDL_GetMouseState(&inputs.mouseX, &inputs.mouseY);
}

void Editor::Window::update()
{
  if (inputs.mouseDown)
  {
    if (!inputs.oldMouseDown) // Click
    {
      toolManager->update(MouseState::CLICK, inputs);
    }
  }
}

static void drawGrid(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 36, 82, 94, 255);
  // Draw vertical lines
  for (int i = 1; i < Editor::Constants::Window.width / Editor::Constants::Grid.size; i++)
    SDL_RenderDrawLine(renderer, i * Editor::Constants::Grid.size, 0, i * Editor::Constants::Grid.size, Editor::Constants::Window.height);
  // Draw horizontal lines
  for (int i = 1; i < Editor::Constants::Window.height / Editor::Constants::Grid.size; i++)
    SDL_RenderDrawLine(renderer, 0, i * Editor::Constants::Grid.size, Editor::Constants::Window.width, i * Editor::Constants::Grid.size);
}

void Editor::Window::draw()
{
  renderer->setDrawColor(10, 56, 69, 255);
  renderer->clear();

  drawGrid(renderer->getSDL());
  // Draw the toolbar
  SDL_Color c = toolManager->getColor();
  renderer->setDrawColor(c.r, c.g, c.b, 255);
  SDL_Rect toolbar = {0, Constants::Window.height - Constants::Window.toolBarHeight, Constants::Window.width, Constants::Window.toolBarHeight};
  SDL_RenderFillRect(renderer->getSDL(), &toolbar);
  toolManager->draw();

  renderer->present();
}
