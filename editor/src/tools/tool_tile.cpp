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

Editor::Tool::Tile::Col::Col(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Col", x , y)
{
  for (int i = 0; i < 10; ++i)
  {
    TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
    SDL_Surface* txtSurface = TTF_RenderText_Blended(font, std::to_string(i).c_str(), {255, 255, 255});
    numberTexs[i] = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txtSurface));
    SDL_FreeSurface(txtSurface);
    TTF_CloseFont(font);
  }
}

Editor::Tool::Tile::Col::~Col()
{
  for (int i = 0; i < 10; ++i)
    delete numberTexs[i];
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
      int digits = 6;
      // Up button
      if (Window::get_inputs().mouseX >= x + WIDTH + 16 * digits &&
          Window::get_inputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouseY >= y &&
          Window::get_inputs().mouseY < y + HEIGHT)
      {
        Window::selected_tool = nullptr;

        if (Window::data.map.sections[0].size.x < 999999)
        {
          // Increase column and add new tiles
          // Visual might be posted sometime, idk...
          ++Window::data.map.sections[0].size.x;
          Window::data.map.sections[0].tiles.reserve(Window::data.map.sections[0].size.x * Window::data.map.sections[0].size.y);

          // Make the new size
          for (unsigned int i = 0; i < Window::data.map.sections[0].size.y; ++i)
            Window::data.map.sections[0].tiles.push_back(Data::Types::Map::Tile());

          // Move the elements
          std::vector<Data::Types::Map::Tile>::iterator i = Window::data.map.sections[0].tiles.end(), begin = Window::data.map.sections[0].tiles.begin();
          i -= Window::data.map.sections[0].size.y + (Window::data.map.sections[0].size.x - 1);
          while (i > begin)
          {
            std::copy(i, i + (Window::data.map.sections[0].size.x - 1), i + (i - begin) / (Window::data.map.sections[0].size.x - 1));
            i -= (Window::data.map.sections[0].size.x - 1);
          }

          // Actually add the new elements
          for (std::vector<Data::Types::Map::Tile>::iterator j = (begin + Window::data.map.sections[0].size.x - 1); j < Window::data.map.sections[0].tiles.end(); j += Window::data.map.sections[0].size.x)
          {
            *j = Data::Types::Map::Tile();
          }
        }
      }

      // Down button
      if (Window::get_inputs().mouseX >= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT * 2 &&
          Window::get_inputs().mouseY >= y &&
          Window::get_inputs().mouseY < y + HEIGHT)
      {
        Window::selected_tool = nullptr;

        if (Window::data.map.sections[0].size.x > 1 && Window::getFirstTile() % Window::data.map.sections[0].size.x != Window::data.map.sections[0].size.x - 1) // Map size has to be greater than 1, sorry
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
            std::vector<Data::Types::Map::Tile>::iterator i = Window::data.map.sections[0].tiles.begin() + Window::data.map.sections[0].size.x;
            unsigned int decAmount = 1;
            while (i < Window::data.map.sections[0].tiles.end())
            {
              std::copy(i, i + (Window::data.map.sections[0].size.x - 1), i - decAmount++);
              i += Window::data.map.sections[0].size.x;
            }
            Window::data.map.sections[0].tiles.erase(Window::data.map.sections[0].tiles.end() - Window::data.map.sections[0].size.y, Window::data.map.sections[0].tiles.end());

            --Window::data.map.sections[0].size.x;
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

void Editor::Tool::Tile::Col::draw()
{
  Base::draw();

  // Draw the current number of columns
  int digits = 6;
  for (int i = digits, x = 0; i > 0; --i, ++x)
  {
    int digit = static_cast<int>(Window::data.map.sections[0].size.x / std::pow(10, i - 1)) % 10;
    SDL_Rect dRect = {x + WIDTH + 16 * x, y, 0, 0};
    SDL_QueryTexture(numberTexs[digit]->get_SDL(), 0, 0, &dRect.w, &dRect.h);
    dRect.y += (HEIGHT - dRect.h) / 2;
    renderer->copy(numberTexs[digit], 0, &dRect);
  }

  // Draw the increase / decrease boxes
  // Points
  SDL_Point upPoints[4] = {
    {x + WIDTH + 16 * digits + 8,              y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + 8 + (HEIGHT - 16) / 2, y   + 8},
    {x + WIDTH + 16 * digits - 8 + HEIGHT,     y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + 8,              y + HEIGHT - 8}
  };
  SDL_Point downPoints[4] = {
    {x + WIDTH + 16 * digits + HEIGHT + 8,                     y          + 8},
    {x + WIDTH + 16 * digits + HEIGHT + 8 + (HEIGHT - 16) / 2, y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + HEIGHT - 8 + HEIGHT,            y          + 8},
    {x + WIDTH + 16 * digits + HEIGHT + 8,                     y          + 8}
  };
  renderer->set_draw_color(255, 255, 255, 255);
  SDL_RenderDrawLines(renderer->get_SDL(), upPoints, 4);
  SDL_RenderDrawLines(renderer->get_SDL(), downPoints, 4);
}

/*
 * ========================================
 * Row(s) Tool
 * ========================================
 */

Editor::Tool::Tile::Row::Row(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Row", x , y)
{
  for (int i = 0; i < 10; ++i)
  {
    TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
    SDL_Surface* txtSurface = TTF_RenderText_Blended(font, std::to_string(i).c_str(), {255, 255, 255});
    numberTexs[i] = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txtSurface));
    SDL_FreeSurface(txtSurface);
    TTF_CloseFont(font);
  }
}

Editor::Tool::Tile::Row::~Row()
{
  for (int i = 0; i < 10; ++i)
    delete numberTexs[i];
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
      int digits = 6;
      // Up button
      if (Window::get_inputs().mouseX >= x + WIDTH + 16 * digits &&
          Window::get_inputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouseY >= y &&
          Window::get_inputs().mouseY < y + HEIGHT)
      {
        Window::selected_tool = nullptr;

        if (Window::data.map.sections[0].size.y < 999999)
        {
          // Increase row and add tiles
          // This is way easier than the columns
          // Simply just append column amount of tiles to the vector
          ++Window::data.map.sections[0].size.y;
          Window::data.map.sections[0].tiles.reserve(Window::data.map.sections[0].size.x + Window::data.map.sections[0].size.y);

          for (unsigned int i = 0; i < Window::data.map.sections[0].size.x; ++i)
          {
            Window::data.map.sections[0].tiles.push_back(Data::Types::Map::Tile());
          }
        }
      }

      // Down button
      if (Window::get_inputs().mouseX >= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT * 2 &&
          Window::get_inputs().mouseY >= y &&
          Window::get_inputs().mouseY < y + HEIGHT)
      {
        Window::selected_tool = nullptr;

        if (Window::data.map.sections[0].size.y > 1 && Window::getFirstTile() % Window::data.map.sections[0].size.y != Window::data.map.sections[0].size.y - 1) // Map size has to be greater than 1, sorry
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
            --Window::data.map.sections[0].size.y;
            Window::data.map.sections[0].tiles.erase(Window::data.map.sections[0].tiles.end() - Window::data.map.sections[0].size.x, Window::data.map.sections[0].tiles.end());
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

void Editor::Tool::Tile::Row::draw()
{
  Base::draw();

  // Draw the current number of columns
  int digits = 6;
  for (int i = digits, x = 0; i > 0; --i, ++x)
  {
    int digit = static_cast<int>(Window::data.map.sections[0].size.y / std::pow(10, i - 1)) % 10;
    SDL_Rect dRect = {x + WIDTH + 16 * x, y, 0, 0};
    SDL_QueryTexture(numberTexs[digit]->get_SDL(), 0, 0, &dRect.w, &dRect.h);
    dRect.y += (HEIGHT - dRect.h) / 2;
    renderer->copy(numberTexs[digit], 0, &dRect);
  }

  // Draw the increase / decrease boxes
  // Points
  SDL_Point upPoints[4] = {
    {x + WIDTH + 16 * digits + 8,              y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + 8 + (HEIGHT - 16) / 2, y   + 8},
    {x + WIDTH + 16 * digits - 8 + HEIGHT,     y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + 8,              y + HEIGHT - 8}
  };
  SDL_Point downPoints[4] = {
    {x + WIDTH + 16 * digits + HEIGHT + 8,                     y          + 8},
    {x + WIDTH + 16 * digits + HEIGHT + 8 + (HEIGHT - 16) / 2, y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + HEIGHT - 8 + HEIGHT,            y          + 8},
    {x + WIDTH + 16 * digits + HEIGHT + 8,                     y          + 8}
  };
  renderer->set_draw_color(255, 255, 255, 255);
  SDL_RenderDrawLines(renderer->get_SDL(), upPoints, 4);
  SDL_RenderDrawLines(renderer->get_SDL(), downPoints, 4);
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
  tools.push_back(new ID             (renderer, x + WIDTH + 16 * (6) + HEIGHT * 2, initialY + HEIGHT * 0));
  tools.push_back(new TopCollision   (renderer, x + WIDTH + 16 * (6) + HEIGHT * 2, initialY + HEIGHT * 1));
  tools.push_back(new RightCollision (renderer, x + WIDTH + 16 * (6) + HEIGHT * 2, initialY + HEIGHT * 2));
  tools.push_back(new BottomCollision(renderer, x + WIDTH + 16 * (6) + HEIGHT * 2, initialY + HEIGHT * 3));
  tools.push_back(new LeftCollision  (renderer, x + WIDTH + 16 * (6) + HEIGHT * 2, initialY + HEIGHT * 4));
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
        if (my < Constants::Window.height - Constants::Window.toolBarHeight)
        {
          int gridX = Window::get_inputs().mouseX / Constants::Grid.size;
          int gridY = Window::get_inputs().mouseY / Constants::Grid.size;

          unsigned int sizeX = Window::data.map.sections[0].size.x;
          unsigned int sizeY = Window::data.map.sections[0].size.y;
          size_t firstTile = Window::getFirstTile();

          unsigned int windowXTiles = Constants::Window.width / Constants::Grid.size;
          unsigned int maxXTiles = sizeX - (firstTile % sizeX) < windowXTiles ? sizeX - (firstTile % sizeX) : windowXTiles;
          unsigned int windowYTiles = (Constants::Window.height - Constants::Window.toolBarHeight) / Constants::Grid.size;
          unsigned int maxYTiles = sizeY - (firstTile / sizeY) < windowYTiles ? sizeY - (firstTile / sizeY) : windowYTiles;
          if (gridX <= maxXTiles && gridY <= maxYTiles)
          {
            selectedTile = &Window::data.map.sections[0].tiles[firstTile + gridX + (sizeX * (firstTile + gridY))];
            selectedTileRect = {gridX * Constants::Grid.size, gridY * Constants::Grid.size, Constants::Grid.size, Constants::Grid.size};
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
    selectedTile = nullptr;
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

  if (selectedTile != nullptr)
  {
    // Draw the hover
    renderer->set_draw_color(255, 255, 255, 128);
    SDL_RenderFillRect(renderer->get_SDL(), &selectedTileRect);

    // Draw the tools
    for (Base* t : tools)
      t->draw();
  }

  if (Window::selected_tool == this)
  {
    // Determine snap hover
    if (Window::get_inputs().mouseY < Constants::Window.height - Constants::Window.toolBarHeight) // Above tool area
    {
      // Make sure not selecting on a tab
      if (Window::get_inputs().mouseY > Constants::Window.height - Constants::Window.toolBarHeight - Constants::Grid.size)
        if (!(Window::get_inputs().mouseX > Constants::Grid.size * 2 && Window::get_inputs().mouseX < Constants::Window.width - Constants::Grid.size * 6))
          return;

      int gridX = Window::get_inputs().mouseX / Constants::Grid.size * Constants::Grid.size;
      int gridY = Window::get_inputs().mouseY / Constants::Grid.size * Constants::Grid.size;
      SDL_Rect dRect = {gridX, gridY, Constants::Grid.size, Constants::Grid.size};
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

Editor::Tool::Tile::Edit::ID::ID(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "ID", x , y)
{
  for (int i = 0; i < 10; ++i)
  {
    TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
    SDL_Surface* txtSurface = TTF_RenderText_Blended(font, std::to_string(i).c_str(), {255, 255, 255});
    numberTexs[i] = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txtSurface));
    SDL_FreeSurface(txtSurface);
    TTF_CloseFont(font);
  }
}

Editor::Tool::Tile::Edit::ID::~ID()
{
  for (int i = 0; i < 10; ++i)
  {
    delete numberTexs[i];
  }
}

void Editor::Tool::Tile::Edit::ID::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::HOVER:
    {
       break;
    }
    case MouseState::CLICK:
    {
      int digits = 6;
      // Up button
      if (Window::get_inputs().mouseX >= x + WIDTH + 16 * digits &&
          Window::get_inputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouseY >= y &&
          Window::get_inputs().mouseY < y + HEIGHT)
      {
        if (dynamic_cast<Main*>(Window::selected_tool)->selectedTile->id < 999999)
        {
          ++dynamic_cast<Main*>(Window::selected_tool)->selectedTile->id;
        }
      }

      // Down button
      if (Window::get_inputs().mouseX >= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT * 2 &&
          Window::get_inputs().mouseY >= y &&
          Window::get_inputs().mouseY < y + HEIGHT)
      {
        if (dynamic_cast<Main*>(Window::selected_tool)->selectedTile->id > 0) // Map size has to be greater than 1, sorry
        {
          --dynamic_cast<Main*>(Window::selected_tool)->selectedTile->id;
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

void Editor::Tool::Tile::Edit::ID::draw()
{
  Base::draw();

  // Draw the current number of columns
  int digits = 6;
  for (int i = digits, x = 0; i > 0; --i, ++x)
  {
    int digit = static_cast<int>(dynamic_cast<Main*>(Window::selected_tool)->selectedTile->id / std::pow(10, i - 1)) % 10;
    SDL_Rect dRect = {Base::x + x + WIDTH + 16 * x, y, 0, 0};
    SDL_QueryTexture(numberTexs[digit]->get_SDL(), 0, 0, &dRect.w, &dRect.h);
    dRect.y += (HEIGHT - dRect.h) / 2;
    renderer->copy(numberTexs[digit], 0, &dRect);
  }

  // Draw the increase / decrease boxes
  // Points
  SDL_Point upPoints[4] = {
    {x + WIDTH + 16 * digits + 8,              y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + 8 + (HEIGHT - 16) / 2, y   + 8},
    {x + WIDTH + 16 * digits - 8 + HEIGHT,     y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + 8,              y + HEIGHT - 8}
  };
  SDL_Point downPoints[4] = {
    {x + WIDTH + 16 * digits + HEIGHT + 8,                     y          + 8},
    {x + WIDTH + 16 * digits + HEIGHT + 8 + (HEIGHT - 16) / 2, y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + HEIGHT - 8 + HEIGHT,            y          + 8},
    {x + WIDTH + 16 * digits + HEIGHT + 8,                     y          + 8}
  };
  renderer->set_draw_color(255, 255, 255, 255);
  SDL_RenderDrawLines(renderer->get_SDL(), upPoints, 4);
  SDL_RenderDrawLines(renderer->get_SDL(), downPoints, 4);
}

/*
 * ========================================
 * Edit::TopCollision Tool
 * ========================================
 */

Editor::Tool::Tile::Edit::TopCollision::TopCollision(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Col-T", x , y)
{
}

Editor::Tool::Tile::Edit::TopCollision::~TopCollision()
{
}

void Editor::Tool::Tile::Edit::TopCollision::update(MouseState ms)
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

void Editor::Tool::Tile::Edit::TopCollision::draw()
{
  Base::draw();
}

/*
 * ========================================
 * Edit::RightCollision Tool
 * ========================================
 */

Editor::Tool::Tile::Edit::RightCollision::RightCollision(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Col-R", x , y)
{
}

Editor::Tool::Tile::Edit::RightCollision::~RightCollision()
{
}

void Editor::Tool::Tile::Edit::RightCollision::update(MouseState ms)
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

void Editor::Tool::Tile::Edit::RightCollision::draw()
{
  Base::draw();
}

/*
 * ========================================
 * Edit::BottomCollision Tool
 * ========================================
 */

Editor::Tool::Tile::Edit::BottomCollision::BottomCollision(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Col-B", x , y)
{
}

Editor::Tool::Tile::Edit::BottomCollision::~BottomCollision()
{
}

void Editor::Tool::Tile::Edit::BottomCollision::update(MouseState ms)
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

void Editor::Tool::Tile::Edit::BottomCollision::draw()
{
  Base::draw();
}

/*
 * ========================================
 * Edit::LeftCollision Tool
 * ========================================
 */

Editor::Tool::Tile::Edit::LeftCollision::LeftCollision(SDLW::Renderer* renderer, int x, int y) : Editor::Tool::Base(renderer, "Col-L", x , y)
{
}

Editor::Tool::Tile::Edit::LeftCollision::~LeftCollision()
{
}

void Editor::Tool::Tile::Edit::LeftCollision::update(MouseState ms)
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

void Editor::Tool::Tile::Edit::LeftCollision::draw()
{
  Base::draw();
}

