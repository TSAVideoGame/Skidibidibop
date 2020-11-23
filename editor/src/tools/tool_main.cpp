#include "tool_main.h"
#include "confirmation_bool.h"
#include "confirmation_string.h"
#include "window.h"

/*
 * ========================================
 * Save Tool
 * ========================================
 */

Editor::Tool::Main::Save::Save(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Save", x , y)
{

}

void Editor::Tool::Main::Save::update(MouseState ms)
{
  Inputs inputs = Window::get_inputs();
  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      if (inputs.mouseX >= x && inputs.mouseX < x + WIDTH && inputs.mouseY >= y && inputs.mouseY < y + HEIGHT)
      {
        Confirmation::Bool confirm("Are you sure?");
        while (confirm.getData()->result == nullptr)
        {
          confirm.input();
          confirm.update();
          confirm.draw();
        }
      }
      break;
    }
    case MouseState::DRAG:
    {
      break;
    }
    case MouseState::RELEASE:
    {
      break;
    }
  }
}

/*
 * ========================================
 * Load Tool
 * ========================================
 */

Editor::Tool::Main::Load::Load(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Load", x , y)
{

}

void Editor::Tool::Main::Load::update(MouseState ms)
{
  Inputs inputs = Window::get_inputs();
  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      if (inputs.mouseX >= x && inputs.mouseX < x + WIDTH && inputs.mouseY >= y && inputs.mouseY < y + HEIGHT)
      {
        Confirmation::String confirm("Type something");
        while (confirm.getData()->result == nullptr)
        {
          confirm.input();
          confirm.update();
          confirm.draw();
        }
        char text[confirm.getData()->size];
        strcpy(text, reinterpret_cast<const char*>(confirm.getData()->result));
        // Text now has the file name
        // TODO: Make sure file can be found, then load it up
      }
      break;
    }
    case MouseState::DRAG:
    {
      break;
    }
    case MouseState::RELEASE:
    {
      break;
    }
  }
}
