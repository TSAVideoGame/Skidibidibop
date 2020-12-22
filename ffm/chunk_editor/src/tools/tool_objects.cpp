#include "tool_objects.h"
#include "window.h"

/*
 * ========================================
 * Edit Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::Objects::Edit::Main::Main(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Edit", x, y)
{
  tools.reserve(1);
  tools.push_back(new Delete(renderer, x, y + (16 +32)));
  
  selected_tool = nullptr;
}

FFM::ChunkEditor::Tools::Objects::Edit::Main::~Main()
{
  for (Base* t : tools)
    delete t;
}

void FFM::ChunkEditor::Tools::Objects::Edit::Main::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (is_hovered(Window::get_inputs()))
      {
        Window::selected_tool = this;
      }

      if (this == Window::selected_tool)
      {
        // Update all tools in case new one is selected
        for (Base* t : tools)
          t->update(ms);
      }

      break;
    }
  }

  if (this == Window::selected_tool && selected_tool)
    selected_tool->update(ms);
}

void FFM::ChunkEditor::Tools::Objects::Edit::Main::draw()
{
  Base::draw();

  if (this == Window::selected_tool)
  {
    for (Base* t : tools)
      t->draw();
  }
}

/*
 * ========================================
 * Edit->Delete Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::Objects::Edit::Delete::Delete(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Delete", x, y)
{

}

void FFM::ChunkEditor::Tools::Objects::Edit::Delete::update(MouseState ms)
{

}

/*
 * ========================================
 * Images
 * ========================================
 */
FFM::ChunkEditor::Tools::Objects::Images::Images(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "Page", x, y, 0, 99999, &page)
{
  page = 0;
  selected_id = -1;
}

void FFM::ChunkEditor::Tools::Objects::Images::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (hover_increment())
      {
        if (*variable < max)
          ++*variable;
      }

      if (hover_decrement())
      {
        if (*variable > min)
          --*variable;
      }
    }
  }
}

void FFM::ChunkEditor::Tools::Objects::Images::draw()
{
  Numeric::draw();

  for (int i = 0; i < PAGE_AMOUNT; ++i)
  {
    SDL_Rect src_rect = {(page * PAGE_AMOUNT + i) * 32, 0, 32, 32};
    SDL_Rect dest_rect = {x, (y + 32 + 8) + i * (32 + 8), 32, 32};
    renderer->copy(Window::get_spritesheet(), &src_rect, &dest_rect);
  }
}
