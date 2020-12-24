#include "tool_collisions.h"
#include "constants.h"

/*
 * ========================================
 * Vertex Tools
 * ========================================
 */
// Add Vertex
FFM::ChunkEditor::Tools::Collisions::Vertex::Add::Add(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "+Vertex", x, y)
{

}

void FFM::ChunkEditor::Tools::Collisions::Vertex::Add::update(MouseState ms)
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
        Inputs in = Window::get_inputs();
        if (in.mouse_x > Constants::Window.TOOL_WIDTH)
        {
          Window::data.vertices.push_back({static_cast<std::uint16_t>(in.mouse_x - Constants::Window.TOOL_WIDTH), static_cast<std::uint16_t>(in.mouse_y)});
        }
      }
    }
  }
}

void FFM::ChunkEditor::Tools::Collisions::Vertex::Add::draw()
{
  Base::draw();

  if (this != Window::selected_tool)
    return;

  Inputs in = Window::get_inputs();
  
  if (in.mouse_x > Constants::Window.TOOL_WIDTH)
  {
    SDL_Rect dest_rect = {in.mouse_x - 5, in.mouse_y - 5, 9, 9};
    renderer->set_draw_color(0, 0, 0, 255);
    SDL_RenderFillRect(renderer->get_SDL(), &dest_rect);
  }
}

// Remove Vertex
FFM::ChunkEditor::Tools::Collisions::Vertex::Remove::Remove(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "-Vertex", x, y)
{

}

void FFM::ChunkEditor::Tools::Collisions::Vertex::Remove::update(MouseState ms)
{

}

/*
 * ========================================
 * Line Tools
 * ========================================
 */
// Add Line
FFM::ChunkEditor::Tools::Collisions::Line::Add::Add(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "+Line", x, y)
{
  v1 = -1;
}

void FFM::ChunkEditor::Tools::Collisions::Line::Add::update(MouseState ms)
{

}

// Remove Line
FFM::ChunkEditor::Tools::Collisions::Line::Remove::Remove(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "+Line", x, y)
{

}

void FFM::ChunkEditor::Tools::Collisions::Line::Remove::update(MouseState ms)
{

}
