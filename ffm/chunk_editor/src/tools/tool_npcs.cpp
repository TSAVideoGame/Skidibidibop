#include "tool_npcs.h"
#include "constants.h"

/*
 * ========================================
 * Edit Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::NPCs::Edit::Main::Main(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Edit", x, y)
{
  tools.reserve(2);
  tools.push_back(new Id    (renderer, x, y + (16 + 32) * 1));
  tools.push_back(new Delete(renderer, x, y + (16 + 32) * 2));
  
  selected_tool = nullptr;
  selected_npc = -1;
}

FFM::ChunkEditor::Tools::NPCs::Edit::Main::~Main()
{
  for (Base* t : tools)
    delete t;
}

void FFM::ChunkEditor::Tools::NPCs::Edit::Main::update(MouseState ms)
{
  if (this != Window::selected_tool)
  {
    selected_npc = -1;
    selected_tool = nullptr;
  }

  Inputs in = Window::get_inputs();
  switch (ms)
  {
    case MouseState::HOVER:
    {
      if (selected_npc != - 1)
      {
        // Move 'tool'
        Data::Types::Chunk::Vertex* v = &Window::npc_vertices[Window::npcs[selected_npc].vertex];
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
        for (int i = 0; i < Window::npcs.size(); ++i)
        {
          Data::Types::Chunk::Vertex v = Window::npc_vertices[Window::npcs[i].vertex];
          int view_x = in.mouse_x - Constants::Window.TOOL_WIDTH;
          if (view_x >= v.x &&
              view_x <  v.x + 32 &&
              in.mouse_y >= v.y &&
              in.mouse_y <  v.y + 32)
          {
            selected_npc = i; 
          }
        }

        if (selected_npc != -1)
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

void FFM::ChunkEditor::Tools::NPCs::Edit::Main::draw()
{
  Base::draw();

  if (this == Window::selected_tool && selected_npc != -1)
  {
    for (Base* t : tools)
      t->draw();
  }
}

/*
 * ========================================
 * Edit->Id Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::NPCs::Edit::Id::Id(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "Id", x, y, 0, 10000, nullptr)
{

}

void FFM::ChunkEditor::Tools::NPCs::Edit::Id::update(MouseState ms)
{
  variable = &Window::npcs[dynamic_cast<NPCs::Edit::Main*>(Window::selected_tool)->selected_npc].id;
  Numeric::update(ms);
}

/*
 * ========================================
 * Edit->Delete Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::NPCs::Edit::Delete::Delete(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Delete", x, y)
{

}

void FFM::ChunkEditor::Tools::NPCs::Edit::Delete::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (is_hovered(Window::get_inputs()))
      {
        int selected_npc = reinterpret_cast<Edit::Main*>(Window::selected_tool)->selected_npc;
        // Swap selected and last objects and their vertices
        // Assumes objects and vertices have nice 1:1 mapping and all
        std::iter_swap(Window::npcs.begin() + selected_npc, Window::npcs.end() - 1);
        std::iter_swap(Window::npc_vertices.begin() + selected_npc, Window::npc_vertices.end() - 1);

        // Update the index of the swapped object's vertex
        Window::npcs[selected_npc].vertex = static_cast<std::uint16_t>(selected_npc);
        // Erase the elements at the end
        Window::npcs.erase(Window::npcs.end() - 1);
        Window::npc_vertices.erase(Window::npc_vertices.end() - 1);

        // De-select the tool
        Window::selected_tool = nullptr;
      }
    }
  }
}

/*
 * ========================================
 * Add Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::NPCs::Add::Add(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Add", x, y)
{
  
}

void FFM::ChunkEditor::Tools::NPCs::Add::update(MouseState ms)
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
          Window::npc_vertices.push_back({static_cast<std::uint16_t>(in.mouse_x - Constants::Window.TOOL_WIDTH), static_cast<std::uint16_t>(in.mouse_y)});
          Window::npcs.push_back({static_cast<std::uint16_t>(Window::npc_vertices.size() - 1), 0});
        }
      }

      break;
    }
  }
}

void FFM::ChunkEditor::Tools::NPCs::Add::draw()
{
  Base::draw();
  if (this == Window::selected_tool)
  {
    Inputs in = Window::get_inputs();

    if (in.mouse_x > Constants::Window.TOOL_WIDTH)
    {
      renderer->set_draw_color(0, 0, 255, 255);
      SDL_Rect dest_rect = {in.mouse_x, in.mouse_y, 32, 32};
      SDL_RenderFillRect(renderer->get_SDL(), &dest_rect);
    }
  }
}
