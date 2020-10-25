#include "tool_tile.h"
#include "confirmation_bool.h"
#include "confirmation_string.h"

/*
 * ========================================
 * Col(umns) Tool
 * ========================================
 */

Editor::Tool::Tile::Col::Col(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Col", x , y)
{

}

void Editor::Tool::Tile::Col::update(MouseState ms)
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

void Editor::Tool::Tile::Col::draw()
{
  Base::draw();
}

/*
 * ========================================
 * Col(umns) Tool
 * ========================================
 */

Editor::Tool::Tile::Row::Row(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Row", x , y)
{

}

void Editor::Tool::Tile::Row::update(MouseState ms)
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

void Editor::Tool::Tile::Row::draw()
{
  Base::draw();
}
