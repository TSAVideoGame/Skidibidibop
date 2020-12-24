#include "tool_objects.h"
#include "window.h"
#include "constants.h"
#include <algorithm>

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
  selected_object = -1;
}

FFM::ChunkEditor::Tools::Objects::Edit::Main::~Main()
{
  for (Base* t : tools)
    delete t;
}

void FFM::ChunkEditor::Tools::Objects::Edit::Main::update(MouseState ms)
{
  if (this != Window::selected_tool)
  {
    selected_object = -1;
    selected_tool = nullptr;
  }

  Inputs in = Window::get_inputs();
  switch (ms)
  {
    case MouseState::HOVER:
    {
      if (selected_object != - 1)
      {
        // Move 'tool'
        Data::Types::Chunk::Vertex* v = &Window::data.vertices[Window::data.objects[selected_object].vertex];
        if (in.up && v->y > 0)
          --v->y;
        if (in.right && v->x < Constants::Window.VIEW_WIDTH)
          ++v->x;
        if (in.down && v->y < Constants::Window.VIEW_HEIGHT)
          ++v->y;
        if (in.left && v->x > 0)
          --v->x;
      }

      break;
    }
    case MouseState::CLICK:
    {
      if (is_hovered(in))
      {
        Window::selected_tool = this;
      }

      if (this == Window::selected_tool)
      {
        // Super inefficient, but it works!
        for (int i = 0; i < Window::data.objects.size(); ++i)
        {
          Data::Types::Chunk::Vertex v = Window::data.vertices[Window::data.objects[i].vertex];
          int view_x = in.mouse_x - Constants::Window.TOOL_WIDTH;
          if (view_x >= v.x &&
              view_x <  v.x + 32 &&
              in.mouse_y >= v.y &&
              in.mouse_y <  v.y + 32)
          {
            selected_object = i; 
          }
        }

        if (selected_object != -1)
        {
          // Update all tools in case new one is selected
          for (Base* t : tools)
            t->update(ms);
        }
      }

      break;
    }
  }
}

void FFM::ChunkEditor::Tools::Objects::Edit::Main::draw()
{
  Base::draw();

  if (this == Window::selected_tool && selected_object != -1)
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
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (is_hovered(Window::get_inputs()))
      {
        int selected_object = reinterpret_cast<Edit::Main*>(Window::selected_tool)->selected_object;
        // Swap selected and last objects / vertices, remap the index for the object, erase the object
        std::iter_swap(Window::data.objects.begin() + selected_object, Window::data.objects.end() - 1);
        std::iter_swap(Window::data.vertices.begin() + selected_object, Window::data.vertices.end() - 1);
        Window::data.objects[selected_object].vertex = static_cast<std::uint16_t>(selected_object);
        Window::data.objects.erase(Window::data.objects.end() - 1);
        Window::data.vertices.erase(Window::data.vertices.end() - 1);

        Window::selected_tool = nullptr;
      }
    }
  }
}

/*
 * ========================================
 * Images
 * ========================================
 */
FFM::ChunkEditor::Tools::Objects::Images::Images(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "Page", x, y, 0, 10000, &page)
{
  page = 0;
  selected_id = -1;
}

void FFM::ChunkEditor::Tools::Objects::Images::update(MouseState ms)
{
  Numeric::update(ms);

  switch (ms)
  {
    case MouseState::CLICK:
    {
      Inputs in = Window::get_inputs();

      if (in.mouse_x >= x && in.mouse_x < x + 32)
      {
        if (in.mouse_y >= y && in.mouse_y < (y + 32 + 8) + PAGE_AMOUNT * (32 + 8))
        {
          selected_id = page * PAGE_AMOUNT + ((in.mouse_y - (y + 32 + 8)) / (32 + 8));
          // Don't select empty sprites (because total may not divide evenly with PAGE_AMOUNT)
          if (selected_id > Constants::Spritesheet.OBJECTS - 1) // -1 because OBJECTS is length while id is index
            selected_id = -1;
        }
      }

      break;
    }
    case MouseState::RELEASE:
    {
      if (selected_id != -1)
      {
        // Actually add the object
        Inputs in = Window::get_inputs();
        if (in.mouse_x > Constants::Window.TOOL_WIDTH)
        {
          Window::data.vertices.push_back({static_cast<std::uint16_t>(in.mouse_x - Constants::Window.TOOL_WIDTH), static_cast<std::uint16_t>(in.mouse_y)});
          Window::data.objects.push_back({static_cast<std::uint16_t>(Window::data.vertices.size() - 1), static_cast<std::uint16_t>(selected_id)});
        }

        // De-select
        selected_id = -1;
      }
    }
  }
}

void FFM::ChunkEditor::Tools::Objects::Images::draw()
{
  // Draw page tools
  Numeric::draw();

  // Draw the objects
  for (int i = 0; i < PAGE_AMOUNT; ++i)
  {
    SDL_Rect src_rect = {(page * PAGE_AMOUNT + i) * 32, 0, 32, 32};
    SDL_Rect dest_rect = {x, (y + 32 + 8) + i * (32 + 8), 32, 32};
    renderer->copy(Window::get_spritesheet(), &src_rect, &dest_rect);
  }

  // Draw the drag n drop object
  if (selected_id != -1)
  {
    SDL_Rect src_rect = {selected_id * 32, 0, 32, 32};
    SDL_Rect dest_rect = {Window::get_inputs().mouse_x, Window::get_inputs().mouse_y, 32, 32};
    renderer->copy(Window::get_spritesheet(), &src_rect, &dest_rect);
  }
}
