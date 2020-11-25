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

/*
 * ========================================
 * Sect(ions) Tool
 * ========================================
 */

Editor::Tool::Main::Section::Section(SDLW::Renderer* renderer_p, int x_p, int y_p) : Editor::Tool::Numeric(renderer_p, "Sect.", x_p, y_p, 0, 999999, nullptr)
{
  current_section = Window::get_current_section();
  variable = &current_section;
}

Editor::Tool::Main::Section::~Section()
{

}

void Editor::Tool::Main::Section::update(MouseState ms)
{
  current_section = Window::get_current_section();

  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      // Up button
      if (hover_increment())
      {
        Window::selected_tool = nullptr;

        if (current_section < max)
        {
          Window::set_current_section(current_section + 1);
        }
      }

      // Down button
      if (hover_decrement())
      {
        Window::selected_tool = nullptr;

        if (current_section > min)
        {
          Window::set_current_section(current_section - 1);
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
 * SectionAdd Tool
 * ========================================
 */

Editor::Tool::Main::SectionAdd::SectionAdd(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Sect+", x , y)
{

}

void Editor::Tool::Main::SectionAdd::update(MouseState ms)
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
        Data::Types::Map::Section s;
        s.size = {1, 1};
        s.tiles.push_back(Data::Types::Map::Tile());
        Window::data.map.sections.push_back(s);

        Window::set_current_section(Window::data.map.sections.size() - 1);
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
 * SectionDelete Tool
 * ========================================
 */

Editor::Tool::Main::SectionDelete::SectionDelete(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Sect-", x , y)
{

}

void Editor::Tool::Main::SectionDelete::update(MouseState ms)
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
        if (Window::data.map.sections.size() > 1 && Window::get_current_section() != Window::data.map.sections.size() - 1)
        {
          Confirmation::Bool confirm("Are you sure (Will delete the last section)");
          while (confirm.getData()->result == nullptr)
          {
            confirm.input();
            confirm.update();
            confirm.draw();
          }
          if (*reinterpret_cast<bool*>(confirm.getData()->result))
          {
            Window::data.map.sections.pop_back();
          }
        }
        break;
      }
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
