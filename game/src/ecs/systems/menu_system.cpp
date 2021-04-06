#include "menu_system.h"
#include "constants.h"
#include <cmath>
#include "core.h"

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Menu> Game::ECS::Systems::menu_system;

int Game::ECS::Systems::Menu::panel = 1;
int Game::ECS::Systems::Menu::slot_selected_left = 0;
int Game::ECS::Systems::Menu::slot_selected_right = 0;
int Game::ECS::Systems::Menu::slot_chosen_left = 0;

static int selected_ticks = 0;
static bool prev_press_u = false, prev_press_r = false, prev_press_d = false, prev_press_l = false;
static bool press_u = false, press_r = false, press_d = false, press_l = false;
void Game::ECS::Systems::Menu::update()
{
  ++selected_ticks;
  
  Input::Data inputs = Core::get_inputs();
  if (inputs.up)
  {
    if (!prev_press_u)
    {
      prev_press_u = true;
      press_u = true;
    }
    else
    {
      press_u = false;
    }
  }
  else
  {
    prev_press_u = false;
    press_u = false;
  }

  if (inputs.right)
  {
    if (!prev_press_r)
    {
      prev_press_r = true;
      press_r = true;
    }
    else
    {
      press_r = false;
    }
  }
  else
  {
    prev_press_r = false;
    press_r = false;
  }

  if (inputs.down)
  {
    if (!prev_press_d)
    {
      prev_press_d = true;
      press_d = true;
    }
    else
    {
      press_d = false;
    }
  }
  else
  {
    prev_press_d = false;
    press_d = false;
  }

  if (inputs.left)
  {
    if (!prev_press_l)
    {
      prev_press_l = true;
      press_l = true;
    }
    else
    {
      press_l = false;
    }
  }
  else
  {
    prev_press_l = false;
    press_l = false;
  }

  // Moving the selection
  if (press_u)
  {
    // Inventory
    if (panel == 1)
    {
      if ((slot_selected_right - 6) / 6 >= 0)
      {
        slot_selected_right -= 6;
      }
    }
    // Hybridization
    else
    {

    }
  }

  // Moving the selection
  if (press_r)
  {
    // Inventory
    if (panel == 1)
    {
      if ((slot_selected_right + 1) / 6 == slot_selected_right / 6)
      {
        ++slot_selected_right;
      }
    }
    // Hybridization
    else
    {
      if (slot_selected_left > 0)
      {
        panel = 1;
      }
      else
      {
        ++slot_selected_left;
      }
    }
  }

  // Moving the selection
  if (press_d)
  {
    // Inventory
    if (panel == 1)
    {
      if ((slot_selected_right + 6) / 6 < 6)
      {
        slot_selected_right += 6;
      }
    }
    // Hybridization
    else
    {

    }
  }

  // Moving the selection
  if (press_l)
  {
    // Inventory
    if (panel == 1)
    {
      if (slot_selected_right % 6 == 0)
      {
        panel = 0;
      }
      else if ((slot_selected_right - 1) / 6 == slot_selected_right / 6)
      {
        --slot_selected_right;
      }
    }
    // Hybridization
    else
    {
      if (slot_selected_left == 1)
      {
        --slot_selected_left;
      }
    }
  }

  // Select something
  if (inputs.attack)
  {
    // Inventory
    if (panel == 1)
    {

    }
    // Hybridization
    else
    {
      slot_chosen_left = slot_selected_left;
    }
  }
}

void Game::ECS::Systems::Menu::draw(SDLW::Renderer* renderer)
{
  // Screen Overlay
  renderer->set_draw_color(0, 0, 0, 128);
  SDL_RenderFillRect(renderer->get_SDL(), nullptr);

  // Inventory Stuff

  // Panel Seperator
  renderer->set_draw_color(255, 255, 255, 255);
  SDL_RenderDrawLine(renderer->get_SDL(), Constants.Window.width / 3, 0, Constants.Window.width / 3, Constants.Window.height);

  // Right side (Inventory)
  {
    const int ROWS = 6;
    const int COLS = 6;
    const int PADDING = (Constants.Window.width * 2 / 3 - 64 * COLS) / (COLS + 1);
    for (int row = 0; row < ROWS; ++row)
    {
      for (int col = 0; col < COLS; ++col)
      {
        SDL_Rect r = {(Constants.Window.width / 3) + PADDING + col * (64 + PADDING), PADDING + row * (64 + PADDING), 64, 64};
        SDL_RenderDrawRect(renderer->get_SDL(), &r);

        if (panel == 1)
        {
          if (row * COLS + col == slot_selected_right)
          {
            r.x += 8;
            r.y += 8;
            r.y += 2 * std::sin(3.141 / 16 * selected_ticks);
            r.w = 8;
            r.h = 8;
            SDL_RenderFillRect(renderer->get_SDL(), &r);
          }
        }
      }
    }
  }

  // Left side (Hybridization/Current Slot)
  {
    // Top two base weapons
    const int BASE_PADDING = (Constants.Window.width / 3 - 128 * 2) / 3;

    for (int i = 0; i < 2; ++i)
    {
      SDL_Rect r = {BASE_PADDING + i * (128 + BASE_PADDING), 128, 128, 128};
      SDL_RenderDrawRect(renderer->get_SDL(), &r);

      if (slot_chosen_left == i)
      {
        r.x = r.x + r.w - 12;
        r.y = r.y + r.h - 12;
        r.w = 8;
        r.h = 8;
        SDL_RenderFillRect(renderer->get_SDL(), &r);
      }

      if (panel == 0)
      {
        if (slot_selected_left == i)
        {
          SDL_Rect r = { BASE_PADDING + i * (128 + BASE_PADDING), 128, 128, 128 };
          r.x += 8;
          r.y += 8;
          r.y += 2 * std::sin(3.141 / 16 * selected_ticks);
          r.w = 8;
          r.h = 8;
          SDL_RenderFillRect(renderer->get_SDL(), &r);
        }
      }
    }

    // Bottom hybridized weapon
    const int BIG_PADDING = (Constants.Window.width / 3 - 256) / 2;

    SDL_Rect r = { BIG_PADDING, 320, 256, 256 };
    SDL_RenderDrawRect(renderer->get_SDL(), &r);
  }
}
