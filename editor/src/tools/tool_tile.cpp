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
    numberTexs[i] = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->getSDL(), txtSurface));
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
      if (Window::getInputs().mouseX >= x + WIDTH + 16 * digits &&
          Window::getInputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT &&
          Window::getInputs().mouseY >= y &&
          Window::getInputs().mouseY < y + HEIGHT)
      {
        if (Window::data.map.size.x < 999999)
        {
          // Increase column and add new tiles
          // Visual might be posted sometime, idk...
          ++Window::data.map.size.x;
          Window::data.map.tiles.reserve(Window::data.map.size.x + Window::data.map.size.y);

          // Make the new size
          for (unsigned int i = 0; i < Window::data.map.size.y; ++i)
            Window::data.map.tiles.push_back(Data::Types::Map::Tile());

          // Move the elements
          std::vector<Data::Types::Map::Tile>::iterator i = Window::data.map.tiles.end(), begin = Window::data.map.tiles.begin();
          i -= Window::data.map.size.y - Window::data.map.size.x;
          while (i > begin)
          {
            std::copy(i, i + Window::data.map.size.x, i + (i - begin) / Window::data.map.size.x);
            i -= Window::data.map.size.x;
          }

          // Actually add the new elements
          for (std::vector<Data::Types::Map::Tile>::iterator j = begin + Window::data.map.size.x; j < Window::data.map.tiles.end(); j += Window::data.map.size.y)
          {
            *j = Data::Types::Map::Tile();
          }
        }
      }

      // Down button
      if (Window::getInputs().mouseX >= x + WIDTH + 16 * digits + HEIGHT &&
          Window::getInputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT * 2 &&
          Window::getInputs().mouseY >= y &&
          Window::getInputs().mouseY < y + HEIGHT)
      {
        if (Window::data.map.size.x > 1) // Map size has to be greater than 1, sorry
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
            std::vector<Data::Types::Map::Tile>::iterator i = Window::data.map.tiles.begin() + Window::data.map.size.x;
            while (i <= Window::data.map.tiles.end() - Window::data.map.size.x)
            {
              std::copy(i, i + (Window::data.map.size.x - 1), i - (i - Window::data.map.tiles.begin()) / Window::data.map.size.y);
              i += Window::data.map.size.x;
            }
            Window::data.map.tiles.erase(Window::data.map.tiles.end() - Window::data.map.size.y, Window::data.map.tiles.end());

            --Window::data.map.size.x;
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
    int digit = static_cast<int>(Window::data.map.size.x / std::pow(10, i - 1)) % 10;
    SDL_Rect dRect = {x + WIDTH + 16 * x, y, 0, 0};
    SDL_QueryTexture(numberTexs[digit]->getSDL(), 0, 0, &dRect.w, &dRect.h);
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
  renderer->setDrawColor(255, 255, 255, 255);
  SDL_RenderDrawLines(renderer->getSDL(), upPoints, 4);
  SDL_RenderDrawLines(renderer->getSDL(), downPoints, 4);
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
    numberTexs[i] = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->getSDL(), txtSurface));
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
      if (Window::getInputs().mouseX >= x + WIDTH + 16 * digits &&
          Window::getInputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT &&
          Window::getInputs().mouseY >= y &&
          Window::getInputs().mouseY < y + HEIGHT)
      {
        if (Window::data.map.size.y < 999999)
        {
          // Increase row and add tiles
          // This is way easier than the columns
          // Simply just append column amount of tiles to the vector
          ++Window::data.map.size.y;
          Window::data.map.tiles.reserve(Window::data.map.size.x + Window::data.map.size.y);

          for (unsigned int i = 0; i < Window::data.map.size.x; ++i)
          {
            Window::data.map.tiles.push_back(Data::Types::Map::Tile());
          }
        }
      }

      // Down button
      if (Window::getInputs().mouseX >= x + WIDTH + 16 * digits + HEIGHT &&
          Window::getInputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT * 2 &&
          Window::getInputs().mouseY >= y &&
          Window::getInputs().mouseY < y + HEIGHT)
      {
        if (Window::data.map.size.y > 1) // Map size has to be greater than 1, sorry
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
            --Window::data.map.size.y;
            Window::data.map.tiles.erase(Window::data.map.tiles.end() - Window::data.map.size.x, Window::data.map.tiles.end());
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
    int digit = static_cast<int>(Window::data.map.size.y / std::pow(10, i - 1)) % 10;
    SDL_Rect dRect = {x + WIDTH + 16 * x, y, 0, 0};
    SDL_QueryTexture(numberTexs[digit]->getSDL(), 0, 0, &dRect.w, &dRect.h);
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
  renderer->setDrawColor(255, 255, 255, 255);
  SDL_RenderDrawLines(renderer->getSDL(), upPoints, 4);
  SDL_RenderDrawLines(renderer->getSDL(), downPoints, 4);
}
