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
        std::string fpath = "res/chunks/" + std::to_string(Window::x) + "_" + std::to_string(Window::y) + ".ffmc";
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
            break;
          }
        }

        std::ofstream save_file(fpath, std::ofstream::trunc | std::ofstream::binary);

        Data::Types::Chunk data;
        // Assign the non-vector members
        data.background_id = Window::background_id;
        data.music_id = Window::music_id;
        data.x = Window::x;
        data.y = Window::y;
        // Populate the non-vertices vectors
        data.objects.reserve(Window::objects.size());
        for (std::vector<Data::Types::Chunk::Object>::iterator i = Window::objects.begin(); i < Window::objects.end(); ++i)
        {
          data.objects.push_back({(*i).id, static_cast<std::uint16_t>((*i).vertex + 0)});
        }

        data.enemies.reserve(Window::monsters.size());
        for (std::vector<Data::Types::Chunk::Enemy>::iterator i = Window::monsters.begin(); i < Window::monsters.end(); ++i)
        {
          data.enemies.push_back({(*i).id, static_cast<std::uint16_t>((*i).vertex + Window::objects.size())});
        }

        data.npcs.reserve(Window::npcs.size());
        for (std::vector<Data::Types::Chunk::NPC>::iterator i = Window::npcs.begin(); i < Window::npcs.end(); ++i)
        {
          data.npcs.push_back({(*i).id, static_cast<std::uint16_t>((*i).vertex + Window::objects.size() + Window::monsters.size())});
        }

        data.lines.reserve(Window::lines.size());
        for (std::vector<Data::Types::Chunk::Line>::iterator i = Window::lines.begin(); i < Window::lines.end(); ++i)
        {
          // This is how I style JS, don't like it but this line is pretty long
          data.lines.push_back({
              static_cast<std::uint16_t>((*i).vertex_1 + Window::objects.size() + Window::monsters.size() + Window::npcs.size()),
              static_cast<std::uint16_t>((*i).vertex_2 + Window::objects.size() + Window::monsters.size() + Window::npcs.size()),
              (*i).flag
          });
        }
        // Populate the vertices vector
        data.vertices.reserve(Window::object_vertices.size() + Window::monster_vertices.size() + Window::npc_vertices.size() + Window::line_vertices.size());
        for (std::vector<Data::Types::Chunk::Vertex>::iterator i = Window::object_vertices.begin(); i < Window::object_vertices.end(); ++i)
        {
          data.vertices.push_back(*i);
        }
        for (std::vector<Data::Types::Chunk::Vertex>::iterator i = Window::monster_vertices.begin(); i < Window::monster_vertices.end(); ++i)
        {
          data.vertices.push_back(*i);
        }
        for (std::vector<Data::Types::Chunk::Vertex>::iterator i = Window::npc_vertices.begin(); i < Window::npc_vertices.end(); ++i)
        {
          data.vertices.push_back(*i);
        }
        for (std::vector<Data::Types::Chunk::Vertex>::iterator i = Window::line_vertices.begin(); i < Window::line_vertices.end(); ++i)
        {
          data.vertices.push_back(*i);
        }

        data.clean();
        data.save(save_file);

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
        std::string fpath = "res/chunks/" + std::to_string(Window::x) + "_" + std::to_string(Window::y) + ".ffmc";

        std::ifstream file(fpath);
        
        if (!file.is_open())
        {
          file.close();
          break;
        }

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

        std::ifstream load_file(fpath, std::ofstream::binary);
        Data::Types::Chunk data;
        data.load(load_file);
        load_file.close();

        // Assign non vector data
        Window::background_id = data.background_id;
        Window::music_id = data.music_id;
        Window::x = data.x;
        Window::y = data.y;
        
        // Assign non-verticies vectors
        Window::objects.clear();
        Window::objects.reserve(data.objects.size());
        for (std::vector<Data::Types::Chunk::Object>::iterator i = data.objects.begin(); i < data.objects.end(); ++i)
        {
          Window::objects.push_back({(*i).id, (*i).vertex});
        }
        
        Window::monsters.clear();
        Window::monsters.reserve(data.enemies.size());
        for (std::vector<Data::Types::Chunk::Enemy>::iterator i = data.enemies.begin(); i < data.enemies.end(); ++i)
        {
          Window::monsters.push_back({(*i).id, static_cast<std::uint16_t>((*i).vertex - data.objects.size())});
        }

        Window::npcs.clear();
        Window::npcs.reserve(data.npcs.size());
        for (std::vector<Data::Types::Chunk::NPC>::iterator i = data.npcs.begin(); i < data.npcs.end(); ++i)
        {
          Window::npcs.push_back({(*i).id, static_cast<std::uint16_t>((*i).vertex - (data.objects.size() + data.enemies.size()))});
        }
        
        Window::lines.clear();
        Window::lines.reserve(data.lines.size());
        for (std::vector<Data::Types::Chunk::Line>::iterator i = data.lines.begin(); i < data.lines.end(); ++i)
        {
          Window::lines.push_back({
              static_cast<std::uint16_t>((*i).vertex_1 - (data.objects.size() + data.enemies.size() + data.npcs.size())),
              static_cast<std::uint16_t>((*i).vertex_2 - (data.objects.size() + data.enemies.size() + data.npcs.size())),
              (*i).flag
          });
        }
        
        // Assign verticies vectors
        for (std::vector<Data::Types::Chunk::Vertex>::iterator i = data.vertices.begin(); i < data.vertices.begin() + data.num_objects; ++i)
        {
          Window::object_vertices.push_back(*i);
        }

        for (std::vector<Data::Types::Chunk::Vertex>::iterator i = data.vertices.begin() + data.num_objects; i < data.vertices.begin() + data.num_objects + data.num_enemies; ++i)
        {
          Window::monster_vertices.push_back(*i);
        }

        for (std::vector<Data::Types::Chunk::Vertex>::iterator i = data.vertices.begin() + data.num_objects + data.num_enemies; i < data.vertices.begin() + data.num_objects + data.num_enemies + data.num_npcs; ++i)
        {
          Window::npc_vertices.push_back(*i);
        }

        
        for (std::vector<Data::Types::Chunk::Vertex>::iterator i = data.vertices.begin() + data.num_objects + data.num_enemies + data.num_npcs; i < data.vertices.end(); ++i)
        {
          Window::line_vertices.push_back(*i);
        }

        break;
      }
    }
  }

}

/*
 * ========================================
 * Background
 *
 * Can store up to 4 million but only draws
 * up to 6 digits...
 * ========================================
 */
FFM::ChunkEditor::Tools::Main::Background::Background(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "Bckg.", x, y, 0, 4000000, &Window::background_id)
{
  prev_id = Window::background_id;
}

void FFM::ChunkEditor::Tools::Main::Background::update(MouseState ms)
{
  Numeric::update(ms);

  if (prev_id != *variable)
  {
    prev_id = *variable;
    Window::update_background();
  }
}

/*
 * ========================================
 * Music
 * ========================================
 */
FFM::ChunkEditor::Tools::Main::Music::Music(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "Music", x, y, 0, 10000, &Window::music_id)
{

}

/*
 * ========================================
 * PosX Tool (Position X)
 * ========================================
 */
FFM::ChunkEditor::Tools::Main::PosX::PosX(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "X", x, y, 0, 10000, &Window::x)
{

}

/*
 * ========================================
 * PosY Tool (Position Y)
 * ========================================
 */
FFM::ChunkEditor::Tools::Main::PosY::PosY(SDLW::Renderer* renderer, int x, int y) : Numeric(renderer, "Y", x, y, 0, 10000, &Window::y)
{

}
