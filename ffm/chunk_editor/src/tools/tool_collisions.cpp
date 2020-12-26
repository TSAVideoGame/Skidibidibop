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
          Window::line_vertices.push_back({static_cast<std::uint16_t>(in.mouse_x - Constants::Window.TOOL_WIDTH), static_cast<std::uint16_t>(in.mouse_y)});
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
        
        }
      }
    }
  }
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

#include <iostream>
void FFM::ChunkEditor::Tools::Collisions::Line::Add::update(MouseState ms)
{
  if (this != Window::selected_tool)
    v1 = -1;

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
          for (std::size_t i = 0; i < Window::line_vertices.size(); ++i)
          {
            FFM::Data::Types::Chunk::Vertex v = Window::line_vertices[i];

            if (in.mouse_x - Constants::Window.TOOL_WIDTH >= v.x - 5 &&
                in.mouse_x - Constants::Window.TOOL_WIDTH <  v.x + 5 &&
                in.mouse_y >= v.y - 5 &&
                in.mouse_y <  v.y + 5)
            {
              if (v1 == -1)
              {
                v1 = i;
              }
              else
              {
                // Points must be different
                if (v1 == i)
                  break;

                Window::lines.push_back({static_cast<std::uint16_t>(v1), static_cast<std::uint16_t>(i), 0});
                v1 = -1;
              }
              break;
            }
          }
        }
      }
    }
  }

}

// Remove Line
FFM::ChunkEditor::Tools::Collisions::Line::Remove::Remove(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "-Line", x, y)
{

}

void FFM::ChunkEditor::Tools::Collisions::Line::Remove::update(MouseState ms)
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
          for (std::vector<Data::Types::Chunk::Line>::iterator i = Window::lines.begin(); i < Window::lines.end(); ++i)
          {
            // Precise line check, this is super inefficient, but only happens on clicks when this tool is selected
            Data::Types::Chunk::Vertex a, b, c;
            a = {Window::line_vertices[(*i).vertex_1].x, Window::line_vertices[(*i).vertex_1].y};
            b = {Window::line_vertices[(*i).vertex_2].x, Window::line_vertices[(*i).vertex_2].y};
            c = {static_cast<std::uint16_t>(in.mouse_x - Constants::Window.TOOL_WIDTH), static_cast<std::uint16_t>(in.mouse_y)};

            // Copying this from another one of my projects
            float distance = std::abs((a.y - b.y) * c.x - (a.x - b.x) * c.y + a.x * b.y - a.y * b.x)
                              / static_cast<float>(std::sqrt(std::pow(a.y - b.y, 2) + std::pow(a.x - b.x, 2)));

            // Hovered
            if (distance < 2.0)
            {
              // Just delete the line, no vertices

              // Swap
              std::iter_swap(i, Window::lines.end() - 1); // Swap the lines
              // Update the indices
              // Iterators will still point to same objects, meaning the object at the end has the correct vertices
              (*i).vertex_1 = (*(Window::lines.end() - 1)).vertex_1;
              (*i).vertex_2 = (*(Window::lines.end() - 1)).vertex_2;

              // Erase the deleted objects
              Window::lines.erase(Window::lines.end() - 1);

              break;
            }
          }
        }
      }
    }
  }
}

/*
 * ========================================
 * Clear All Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::Collisions::Clear::Clear(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Clear", x, y)
{
}

void FFM::ChunkEditor::Tools::Collisions::Clear::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (is_hovered(Window::get_inputs()))
      {
        Window::selected_tool = nullptr;

        Window::lines.clear();
        Window::line_vertices.clear();
      }
      break;
    }
  }
}
