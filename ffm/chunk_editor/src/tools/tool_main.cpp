#include "tool_main.h"
#include "window.h"
#include <string>
#include <fstream>
#include "ffm_data.h"
#include "confirmation_bool.h"

/*
 * ========================================
 * Save Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::Main::Save::Save(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Save", x, y)
{

}

void FFM::ChunkEditor::Tools::Main::Save::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (is_hovered(Window::get_inputs()))
      {
        std::string fpath = "res/chunks/" + std::to_string(Window::data.x) + "_" + std::to_string(Window::data.y) + ".ffmc";
        std::ifstream file(fpath);
        // Always confirm before overwriting file
        if (file.is_open())
        {
          Confirmation::Bool confirm("This operation will overwrite " + fpath + ". Are you sure?");
          while (confirm.get_data()->result == nullptr)
          {
            // This will eat up CPU usage
            confirm.input();
            confirm.update();
            confirm.draw();
          }

          if (!*reinterpret_cast<bool*>(confirm.get_data()->result))
          {
            file.close();
            return;
          }
        }

        std::ofstream save_file(fpath, std::ofstream::trunc | std::ofstream::binary);
        Window::data.clean();
        Window::data.save(save_file);
        save_file.close();

        break;
      }
    }
  }
}

/*
 * ========================================
 * Load Tool
 * ========================================
 */
FFM::ChunkEditor::Tools::Main::Load::Load(SDLW::Renderer* renderer, int x, int y) : Base(renderer, "Load", x, y)
{

}

void FFM::ChunkEditor::Tools::Main::Load::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (is_hovered(Window::get_inputs()))
      {
        std::string fpath = "res/chunks/" + std::to_string(Window::data.x) + "_" + std::to_string(Window::data.y) + ".ffmc";

        Confirmation::Bool confirm("This operation will overwrite the current data in the editor. Are you sure?");
        while (confirm.get_data()->result == nullptr)
        {
          // This will eat up CPU usage
          confirm.input();
          confirm.update();
          confirm.draw();
        }

        if (!*reinterpret_cast<bool*>(confirm.get_data()->result))
        {
          return;
        }

        std::ifstream save_file(fpath, std::ofstream::trunc | std::ofstream::binary);
        Window::data.load(save_file);
        save_file.close();

        break;
      }
    }
  }

}

/*
 * ========================================
 * PosX Tool (Position X)
 * ========================================
 */
FFM::ChunkEditor::Tools::Main::PosX::PosX(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "X", x, y, 0, std::pow(2, 16), &Window::data.x)
{

}

void FFM::ChunkEditor::Tools::Main::PosX::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (hover_increment())
      {
        if (*variable < max)
        {
          ++*variable;
          Window::update_background();
        }
      }

      if (hover_decrement())
      {
        if (*variable > min)
        {
          --*variable;
          Window::update_background();
        }
      }

      break;
    }
  }
}

/*
 * ========================================
 * PosY Tool (Position Y)
 * ========================================
 */
FFM::ChunkEditor::Tools::Main::PosY::PosY(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "Y", x, y, 0, std::pow(2, 16), &Window::data.y)
{

}

void FFM::ChunkEditor::Tools::Main::PosY::update(MouseState ms)
{
  switch (ms)
  {
    case MouseState::CLICK:
    {
      if (hover_increment())
      {
        if (*variable < max)
        {
          ++*variable;
          Window::update_background();
        }
      }

      if (hover_decrement())
      {
        if (*variable > min)
        {
          --*variable;
          Window::update_background();
        }
      }

      break;
    }
  }
}

