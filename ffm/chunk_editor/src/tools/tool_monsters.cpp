#include "tool_monsters.h"
#include "constants.h"

/*
 * ========================================
 * Edit Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::Monsters::Edit::Main::Main(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Edit", x, y)
{
  tools.reserve(2);
  tools.push_back(new Id    (renderer, x, y + (16 + 32) * 1));
  tools.push_back(new Delete(renderer, x, y + (16 + 32) * 2));
  
  selected_tool = nullptr;
  selected_monster = -1;
}

FFM::ChunkEditor::Tools::Monsters::Edit::Main::~Main()
{
  for (Base* t : tools)
    delete t;
}

void FFM::ChunkEditor::Tools::Monsters::Edit::Main::update(MouseState ms)
{
  if (this != Window::selected_tool)
  {
    selected_monster = -1;
    selected_tool = nullptr;
  }

  Inputs in = Window::get_inputs();
  switch (ms)
  {
    case MouseState::HOVER:
    {
      if (selected_monster != - 1)
      {
        // Move 'tool'
        Data::Types::Chunk::Vertex* v = &Window::monster_vertices[Window::monsters[selected_monster].vertex];
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
        for (int i = 0; i < Window::monsters.size(); ++i)
        {
          Data::Types::Chunk::Vertex v = Window::monster_vertices[Window::monsters[i].vertex];
          int view_x = in.mouse_x - Constants::Window.TOOL_WIDTH;
          if (view_x >= v.x &&
              view_x <  v.x + 32 &&
              in.mouse_y >= v.y &&
              in.mouse_y <  v.y + 32)
          {
            selected_monster = i; 
          }
        }

        if (selected_monster != -1)
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

void FFM::ChunkEditor::Tools::Monsters::Edit::Main::draw()
{
  Base::draw();

  if (this == Window::selected_tool && selected_monster != -1)
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
FFM::ChunkEditor::Tools::Monsters::Edit::Id::Id(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "Id", x, y, 0, 10000, nullptr)
{

}

void FFM::ChunkEditor::Tools::Monsters::Edit::Id::update(MouseState ms)
{
  variable = &Window::monsters[dynamic_cast<Monsters::Edit::Main*>(Window::selected_tool)->selected_monster].id;
  Numeric::update(ms);
}

/*
 * ========================================
 * Edit->Delete Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::Monsters::Edit::Delete::Delete(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Delete", x, y)
{

}

void FFM::ChunkEditor::Tools::Monsters::Edit::Delete::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (is_hovered(Window::get_inputs()))
      {
        int selected_monster = reinterpret_cast<Edit::Main*>(Window::selected_tool)->selected_monster;
        // Swap selected and last objects and their vertices
        // Assumes objects and vertices have nice 1:1 mapping and all
        std::iter_swap(Window::monsters.begin() + selected_monster, Window::monsters.end() - 1);
        std::iter_swap(Window::monster_vertices.begin() + selected_monster, Window::monster_vertices.end() - 1);

        // Update the index of the swapped object's vertex
        Window::monsters[selected_monster].vertex = static_cast<std::uint16_t>(selected_monster);
        // Erase the elements at the end
        Window::monsters.erase(Window::monsters.end() - 1);
        Window::monster_vertices.erase(Window::monster_vertices.end() - 1);

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
FFM::ChunkEditor::Tools::Monsters::Add::Add(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Add", x, y)
{
  
}

void FFM::ChunkEditor::Tools::Monsters::Add::update(MouseState ms)
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
          Window::monster_vertices.push_back({static_cast<std::uint16_t>(in.mouse_x - Constants::Window.TOOL_WIDTH), static_cast<std::uint16_t>(in.mouse_y)});
          Window::monsters.push_back({static_cast<std::uint16_t>(Window::monster_vertices.size() - 1), 0});
        }
      }

      break;
    }
  }
}

void FFM::ChunkEditor::Tools::Monsters::Add::draw()
{
  Base::draw();
  if (this == Window::selected_tool)
  {
    Inputs in = Window::get_inputs();

    if (in.mouse_x > Constants::Window.TOOL_WIDTH)
    {
      renderer->set_draw_color(255, 0, 0, 255);
      SDL_Rect dest_rect = {in.mouse_x, in.mouse_y, 32, 32};
      SDL_RenderFillRect(renderer->get_SDL(), &dest_rect);
    }
  }
}
