#include "tool_tile.h"
#include "confirmation_bool.h"
#include "confirmation_string.h"
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include <cmath>
#include <algorithm>


// Terrible code coming up ahead for these two tools

/*
 * ========================================
 * Col(umns) Tool
 * ========================================
 */

Editor::Tool::Tile::Col::Col(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Numeric(renderer, "Col", x , y, 1, 999999, &Window::data.map.sections[Window::get_current_section()].size.x)
{

}

Editor::Tool::Tile::Col::~Col()
{

}

void Editor::Tool::Tile::Col::update(MouseState ms)
{
  variable = &Window::data.map.sections[Window::get_current_section()].size.x; 

  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      // The section to edit
      Data::Types::Map::Section* section = &Window::data.map.sections[Window::get_current_section()];

      // Up button
      if (hover_increment())
      {
        Window::selected_tool = nullptr;

        if (section->size.x < max)
        {
          // Increase column and add new tiles
          // Visual might be posted sometime, idk...
          ++section->size.x;
          section->tiles.reserve(section->size.x * section->size.y);

          // Make the new size
          for (unsigned int i = 0; i < section->size.y; ++i)
            section->tiles.push_back(Data::Types::Map::Tile());

          // Move the elements
          std::vector<Data::Types::Map::Tile>::iterator i = section->tiles.end(), begin = section->tiles.begin();
          i -= section->size.y + (section->size.x - 1);
          while (i > begin)
          {
            std::copy(i, i + (section->size.x - 1), i + (i - begin) / (section->size.x - 1));
            i -= (section->size.x - 1);
          }

          // Actually add the new elements
          for (std::vector<Data::Types::Map::Tile>::iterator j = begin + section->size.x - 1; j < section->tiles.end(); j += section->size.x)
          {
            *j = Data::Types::Map::Tile();
          }
        }
      }

      // Down button
      if (hover_decrement())
      {
        Window::selected_tool = nullptr;

        if (section->size.x > min && Window::get_first_tile() % section->size.x != section->size.x - 1)
        {
          Confirmation::Bool confirm("Are you sure (The entire column will get deleted)");
          while (confirm.getData()->result == nullptr)
          {
            confirm.input();
            confirm.update();
            confirm.draw();
          }
          if (*reinterpret_cast<bool*>(confirm.getData()->result))
          {
            std::vector<Data::Types::Map::Tile>::iterator i = section->tiles.begin() + section->size.x;
            unsigned int decAmount = 1;
            while (i < section->tiles.end())
            {
              std::copy(i, i + (section->size.x - 1), i - decAmount++);
              i += section->size.x;
            }
            section->tiles.erase(section->tiles.end() - section->size.y, section->tiles.end());

            --section->size.x;
          }
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
 * Row(s) Tool
 * ========================================
 */

Editor::Tool::Tile::Row::Row(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Numeric(renderer, "Row", x , y, 1, 999999, &Window::data.map.sections[Window::get_current_section()].size.y)
{

}

Editor::Tool::Tile::Row::~Row()
{

}

void Editor::Tool::Tile::Row::update(MouseState ms)
{
  variable = &Window::data.map.sections[Window::get_current_section()].size.y;

  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      Data::Types::Map::Section* section = &Window::data.map.sections[Window::get_current_section()];
      // Up button
      if (hover_increment())
      {
        Window::selected_tool = nullptr;

        if (section->size.y < max)
        {
          // Increase row and add tiles
          // This is way easier than the columns
          // Simply just append column amount of tiles to the vector
          ++section->size.y;
          section->tiles.reserve(section->size.x + section->size.y);

          for (unsigned int i = 0; i < section->size.x; ++i)
          {
            section->tiles.push_back(Data::Types::Map::Tile());
          }
        }
      }

      // Down button
      if (hover_decrement())
      {
        Window::selected_tool = nullptr;

        if (section->size.y > 1 && Window::get_first_tile() % section->size.y != section->size.y - 1)
        {
          Confirmation::Bool confirm("Are you sure (The entire row will get deleted)");
          while (confirm.getData()->result == nullptr)
          {
            confirm.input();
            confirm.update();
            confirm.draw();
          }
          if (*reinterpret_cast<bool*>(confirm.getData()->result))
          {
            --section->size.y;
            section->tiles.erase(section->tiles.end() - section->size.x, section->tiles.end());
          }
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
 * Edit::Main Tool
 * ========================================
 */

Editor::Tool::Tile::Edit::Main::Main(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Edit", x , y)
{
  tools.reserve(5);
  int initialY = Constants::Window.height - Constants::Window.toolBarHeight;
  tools.push_back(new ID             (renderer, x + WIDTH * 1 + 16 * ( 6) + HEIGHT * 2, initialY + HEIGHT * 0, 0, 999999, nullptr));
  tools.push_back(new TopCollision   (renderer, x + WIDTH * 1 + 16 * ( 6) + HEIGHT * 2, initialY + HEIGHT * 1, nullptr));
  tools.push_back(new RightCollision (renderer, x + WIDTH * 1 + 16 * ( 6) + HEIGHT * 2, initialY + HEIGHT * 2, nullptr));
  tools.push_back(new BottomCollision(renderer, x + WIDTH * 1 + 16 * ( 6) + HEIGHT * 2, initialY + HEIGHT * 3, nullptr));
  tools.push_back(new LeftCollision  (renderer, x + WIDTH * 1 + 16 * ( 6) + HEIGHT * 2, initialY + HEIGHT * 4, nullptr));
  tools.push_back(new Flag           (renderer, x + WIDTH * 2 + 16 * (12) + HEIGHT * 4, initialY + HEIGHT * 0, 0, 999999, nullptr));
  tools.push_back(new Monster        (renderer, x + WIDTH * 3 + 16 * (18) + HEIGHT * 6, initialY + HEIGHT * 0, 0, 999999, nullptr));
}

Editor::Tool::Tile::Edit::Main::~Main()
{
  for (Base* t : tools)
    delete t;
}

void Editor::Tool::Tile::Edit::Main::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      int mx = Window::get_inputs().mouseX, my = Window::get_inputs().mouseY;
      // Select tool
      if (mx >= x && mx <= x + 64 && my >= y && my <= y + 32)
      {
        if (Window::selected_tool != this)
          Window::selected_tool = this;
        else
          Window::selected_tool = nullptr;
      }
      if (Window::selected_tool == this)
      {
        // Select a tile
        if (my < Constants::Window.height - Constants::Window.toolBarHeight - 32) // - 32 for the tabs
        {
          Data::Types::Map::Section* section = &Window::data.map.sections[Window::get_current_section()];
          int grid_size = Constants::Grid.size / std::pow(2, Window::get_current_zoom());

          int grid_x = Window::get_inputs().mouseX / grid_size;
          int grid_y = Window::get_inputs().mouseY / grid_size;

          unsigned int map_x = section->size.x;
          unsigned int map_y = section->size.y;
          size_t first_tile = Window::get_first_tile();

          unsigned int window_tiles_x = Constants::Window.width / Constants::Grid.size;
          unsigned int max_tiles_x = map_x - (first_tile % map_x) < window_tiles_x ? map_x - (first_tile % map_x) : window_tiles_x;
          unsigned int window_tiles_y = (Constants::Window.height - Constants::Window.toolBarHeight) / Constants::Grid.size;
          unsigned int max_tiles_y = map_y - (first_tile / map_y) < window_tiles_y ? map_y - (first_tile / map_y) : window_tiles_y;
          if (grid_x <= max_tiles_x - 1 && grid_y <= max_tiles_y + 1) // idk cheif, pure mystery
          {
            selected_tile = &section->tiles[first_tile + grid_x + (map_x * (grid_y - first_tile / map_x))];
            selected_tile_num = first_tile + grid_x + (map_x * (grid_y - first_tile / map_x));
          }
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

  if (Window::selected_tool != this)
    selected_tile = nullptr; // selected_tile_num is only used when selected_tile != nullptr, no need to change its value
  else
    for (Base* t : tools)
      t->update(ms);
}

void Editor::Tool::Tile::Edit::Main::draw()
{
  if (Window::selected_tool == this)
    SDL_SetTextureColorMod(texture->get_SDL(), 200, 200, 200);
  else
    SDL_SetTextureColorMod(texture->get_SDL(), 255, 255, 255);
  Base::draw();

  int grid_size = Constants::Grid.size / std::pow(2, Window::get_current_zoom());
  int grid_x = Window::get_inputs().mouseX / grid_size * grid_size;
  int grid_y = Window::get_inputs().mouseY / grid_size * grid_size;

  if (selected_tile != nullptr)
  {
    size_t first_tile = Window::get_first_tile();
    unsigned int map_x = Window::data.map.sections[Window::get_current_section()].size.x;
    unsigned int map_y = Window::data.map.sections[Window::get_current_section()].size.y;
    // Draw the hover
    renderer->set_draw_color(255, 255, 255, 128);
    SDL_Rect selected_tile_rect = {0, 0, grid_size, grid_size};
    selected_tile_rect.x = (selected_tile_num % map_x - first_tile % map_x) * grid_size;
    selected_tile_rect.y = (selected_tile_num / map_y - first_tile / map_y) * grid_size;
    SDL_RenderFillRect(renderer->get_SDL(), &selected_tile_rect);

    // Draw the tools
    for (Base* t : tools)
      t->draw();
  }

  if (Window::selected_tool == this)
  {
    // Determine snap hover
    if (Window::get_inputs().mouseY < Constants::Window.height - Constants::Window.toolBarHeight - 32) // Above tool area (include tab)
    {
      // Make sure not selecting on a tab
      if (Window::get_inputs().mouseY > Constants::Window.height - Constants::Window.toolBarHeight - Constants::Grid.size)
        if (!(Window::get_inputs().mouseX > Constants::Grid.size * 2 && Window::get_inputs().mouseX < Constants::Window.width - Constants::Grid.size * 6))
          return;

      SDL_Rect dRect = {grid_x, grid_y, grid_size, grid_size};
      renderer->set_draw_color(255, 255, 255, 128);
      SDL_RenderFillRect(renderer->get_SDL(), &dRect);
    }
  }
}

/*
 * ========================================
 * Edit::ID Tool
 * ========================================
 */
Editor::Tool::Tile::Edit::ID::ID(SDLW::Renderer* renderer_p, int x_p, int y_p, int min_p, int max_p, std::uint16_t* variable_p) : Editor::Tool::Numeric(renderer_p, "ID", x_p, y_p, min_p, max_p, variable_p)
{

}

Editor::Tool::Tile::Edit::ID::~ID()
{

}

void Editor::Tool::Tile::Edit::ID::update(MouseState ms)
{
  variable = &dynamic_cast<Main*>(Window::selected_tool)->selected_tile->id;

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
        if (*variable < max)
        {
          ++*variable;
        }
      }

      // Down button
      if (hover_decrement())
      {
        if (*variable > min)
        {
          --*variable;
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
 * Edit::TopCollision Tool
 * ========================================
 */

Editor::Tool::Tile::Edit::TopCollision::TopCollision(SDLW::Renderer* renderer_p, int x_p, int y_p, bool* variable_p) : Editor::Tool::Checkbox(renderer_p, "Col-T", x_p, y_p, variable_p)
{

}

Editor::Tool::Tile::Edit::TopCollision::~TopCollision()
{

}

void Editor::Tool::Tile::Edit::TopCollision::update(MouseState ms)
{
  variable = &dynamic_cast<Main*>(Window::selected_tool)->selected_tile->collision.top;

  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      if (hover())
        *variable = !*variable;

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
 * Edit::RightCollision Tool
 * ========================================
 */

Editor::Tool::Tile::Edit::RightCollision::RightCollision(SDLW::Renderer* renderer_p, int x_p, int y_p, bool* variable) : Editor::Tool::Checkbox(renderer_p, "Col-R", x_p, y_p, variable)
{

}

Editor::Tool::Tile::Edit::RightCollision::~RightCollision()
{
}

void Editor::Tool::Tile::Edit::RightCollision::update(MouseState ms)
{
  variable = &dynamic_cast<Main*>(Window::selected_tool)->selected_tile->collision.right;

  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      if (hover())
        *variable = !*variable;

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
 * Edit::BottomCollision Tool
 * ========================================
 */

Editor::Tool::Tile::Edit::BottomCollision::BottomCollision(SDLW::Renderer* renderer_p, int x_p, int y_p, bool* variable_p) : Editor::Tool::Checkbox(renderer_p, "Col-B", x_p , y_p, variable_p)
{
}

Editor::Tool::Tile::Edit::BottomCollision::~BottomCollision()
{
}

void Editor::Tool::Tile::Edit::BottomCollision::update(MouseState ms)
{
  variable = &dynamic_cast<Main*>(Window::selected_tool)->selected_tile->collision.bottom;

  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      if (hover())
        *variable = !*variable;

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
 * Edit::LeftCollision Tool
 * ========================================
 */

Editor::Tool::Tile::Edit::LeftCollision::LeftCollision(SDLW::Renderer* renderer_p, int x_p, int y_p, bool* variable_p) : Editor::Tool::Checkbox(renderer_p, "Col-L", x_p, y_p, variable_p)
{
}

Editor::Tool::Tile::Edit::LeftCollision::~LeftCollision()
{
}

void Editor::Tool::Tile::Edit::LeftCollision::update(MouseState ms)
{
  variable = &dynamic_cast<Main*>(Window::selected_tool)->selected_tile->collision.left;

  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      if (hover())
        *variable = !*variable;

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
 * Edit::Flag Tool
 * ========================================
 */
Editor::Tool::Tile::Edit::Flag::Flag(SDLW::Renderer* renderer_p, int x_p, int y_p, int min_p, int max_p, std::uint16_t* variable_p) : Editor::Tool::Numeric(renderer_p, "Flag", x_p, y_p, min_p, max_p, variable_p)
{

}

Editor::Tool::Tile::Edit::Flag::~Flag()
{

}

void Editor::Tool::Tile::Edit::Flag::update(MouseState ms)
{
  variable = &dynamic_cast<Main*>(Window::selected_tool)->selected_tile->flag;

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
        if (*variable < max)
        {
          ++*variable;
        }
      }

      // Down button
      if (hover_decrement())
      {
        if (*variable > min)
        {
          --*variable;
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
 * Edit::Monster Tool
 * ========================================
 */
Editor::Tool::Tile::Edit::Monster::Monster(SDLW::Renderer* renderer_p, int x_p, int y_p, int min_p, int max_p, std::uint16_t* variable_p) : Editor::Tool::Numeric(renderer_p, "Monst.", x_p, y_p, min_p, max_p, variable_p)
{

}

Editor::Tool::Tile::Edit::Monster::~Monster()
{

}

void Editor::Tool::Tile::Edit::Monster::update(MouseState ms)
{
  variable = &dynamic_cast<Main*>(Window::selected_tool)->selected_tile->enemy_id;

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
        if (*variable < max)
        {
          ++*variable;
        }
      }

      // Down button
      if (hover_decrement())
      {
        if (*variable > min)
        {
          --*variable;
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
