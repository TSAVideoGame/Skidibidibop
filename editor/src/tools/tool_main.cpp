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
        if (*reinterpret_cast<bool*>(confirm.getData()->result))
        {
          Data::Save::save(Window::get_current_file(), Window::data);
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
        Confirmation::String confirm("Enter the name of the file (including the '.sbbd')");
        while (confirm.getData()->result == nullptr)
        {
          confirm.input();
          confirm.update();
          confirm.draw();
        }
        size_t length = confirm.getData()->size;

        if (length < 6) // '.sbbd' + '\0'
          break;

        char text[length];
        strcpy(text, reinterpret_cast<const char*>(confirm.getData()->result));
        // Just checks file extension, nothing fancy here
        if (text[length - 6] == '.' && text[length - 5] == 's' && text[length - 4] == 'b' && text[length - 3] == 'b' && text[length - 2] == 'd')
        {
          Window::set_current_file(text);
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
