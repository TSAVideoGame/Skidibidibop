#include "tool_main.h"
#include "confirmation_bool.h"

/*
 * ========================================
 * Save Tool
 * ========================================
 */

Editor::Tool::Main::Save::Save(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Save", x , y)
{

}

void Editor::Tool::Main::Save::update(MouseState ms, Inputs inputs)
{
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

void Editor::Tool::Main::Load::update(MouseState ms, Inputs inputs)
{
  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
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
 * Col(umns) Tool
 * ========================================
 */

Editor::Tool::Main::Col::Col(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Col", x , y)
{

}

void Editor::Tool::Main::Col::update(MouseState ms, Inputs inputs)
{
  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
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

void Editor::Tool::Main::Col::draw()
{
  Base::draw();
}

/*
 * ========================================
 * Col(umns) Tool
 * ========================================
 */

Editor::Tool::Main::Row::Row(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Row", x , y)
{

}

void Editor::Tool::Main::Row::update(MouseState ms, Inputs inputs)
{
  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
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

void Editor::Tool::Main::Row::draw()
{
  Base::draw();
}
