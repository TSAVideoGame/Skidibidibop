#include "map_system.h"
#include "core.h"
#include "sdlw.h"
#include "camera_system.h"
#include "camera_component.h"
#include <string>
#include <algorithm>

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Map> map_system;

std::vector<FFM::Data::Types::Chunk> Game::ECS::Systems::Map::chunks;
std::uint32_t Game::ECS::Systems::Map::current_chunk = 0;
// Everything involving this (below) is mad sus and dodgy
SDLW::Texture* Game::ECS::Systems::Map::chunk_textures[9];

void Game::ECS::Systems::Map::init()
{
  for (int row = 0; row < 3; ++row)
    for (int col = 0; col < 3; ++col)
    {
      int chunk_index = row * Core::map_helper.x + col;
      if (row < 0 || col < 0)
        chunk_index = -1;

      FFM::Data::Types::Chunk c;
      if (chunk_index >= 0 && chunk_index < Core::map_helper.num_chunks)
      {
        Core::map_file.seekg(Core::map_helper.offsets[chunk_index]);
        c.load(Core::map_file);
      }
      chunks.push_back(c);

      std::string fpath = "res/chunk_images/" + std::to_string(c.background_id) + ".png";
      chunk_textures[row * 3 + col] = new SDLW::Texture(fpath.c_str(), Core::renderer);
    }
}

void Game::ECS::Systems::Map::quit()
{
  for (int i = 0; i < 9; ++i) {
    delete chunk_textures[i];
  }
}

#include <iostream> // Remove later
void Game::ECS::Systems::Map::update()
{
  // Load / Unload chunks
  // TODO: Make these methods for loading/unloading (replace sounds good)
  Camera* cs = Manager::get_instance().get_system<Camera>();
  Components::CameraManager* cm = Components::Manager::get_instance().get_component<Components::CameraManager>();
  Components::CameraManager::Instance cmi = cs->get_active_camera();

  // X
  if (current_chunk % Core::map_helper.x != cm->get_x(cmi) / 800)
  {
    // Load out/in columns
    if (current_chunk % Core::map_helper.x < cm->get_x(cmi) / 800)
    {
      // Load chunks to the right
      if (current_chunk % Core::map_helper.x < Core::map_helper.x - 1)
      {
        ++current_chunk;
        // Fancy rotate stuff
        // The first column needs to be moved to the end
        // Do this by rotating so the 2nd item in a grouping of 3 becomes the first
        // Do this for chunks and chunk_textures
        
        for (int i = 0; i < 3; ++i)
        {
          std::vector<FFM::Data::Types::Chunk>::iterator begin = chunks.begin() + i * 3;
          std::rotate(begin, begin + 1, begin + 3);
        }

        std::vector<SDLW::Texture*> new_textures;
        for (int i = 0; i < 3; ++i)
        {
          new_textures.push_back(chunk_textures[3 * i + 1]);
          new_textures.push_back(chunk_textures[3 * i + 2]);
          new_textures.push_back(chunk_textures[3 * i + 0]);
        }
        std::copy(new_textures.begin(), new_textures.end(), chunk_textures);

        // Add the new chunks / columns
        for (int i = 0; i < 3; ++i)
        {
          FFM::Data::Types::Chunk c;
          if (current_chunk % Core::map_helper.x + 2 < Core::map_helper.x)
          {
            Core::map_file.clear();
            Core::map_file.seekg(Core::map_helper.offsets[Core::map_helper.x * i + current_chunk + 2]);
            c.load(Core::map_file);

            // Load Texture
            std::string fpath = "res/chunk_images/" + std::to_string(c.background_id) + ".png";
            delete chunk_textures[2 + 3 * i];
            chunk_textures[2 + 3 * i] = new SDLW::Texture(fpath.c_str(), Core::renderer);

            // TODO: Load other stuff
          }
          chunks[2 + 3 * i] = c;
        }
      }
    }
    else
    {
      // Load chunk to the left
      if (current_chunk % Core::map_helper.x > 0)
      {
        --current_chunk;
        // Fancy rotate stuff
        // The last column needs to be moved to the beginning
        // Do this by rotating
        // Do this for chunks and chunk_textures
        
        for (int i = 0; i < 3; ++i)
        {
          std::vector<FFM::Data::Types::Chunk>::iterator begin = chunks.begin() + i * 3;
          std::rotate(begin, begin + 2, begin + 3);
        }

        std::vector<SDLW::Texture*> new_textures;
        for (int i = 0; i < 3; ++i)
        {
          new_textures.push_back(chunk_textures[3 * i + 2]);
          new_textures.push_back(chunk_textures[3 * i + 0]);
          new_textures.push_back(chunk_textures[3 * i + 1]);
        }
        std::copy(new_textures.begin(), new_textures.end(), chunk_textures);

        // Add the new chunks / columns
        for (int i = 0; i < 3; ++i)
        {
          FFM::Data::Types::Chunk c;
          // No need to check bounds here
          Core::map_file.clear();
          Core::map_file.seekg(Core::map_helper.offsets[Core::map_helper.x * i + current_chunk]);
          c.load(Core::map_file);

          // Load Texture
          std::string fpath = "res/chunk_images/" + std::to_string(c.background_id) + ".png";
          delete chunk_textures[0 + 3 * i];
          chunk_textures[0 + 3 * i] = new SDLW::Texture(fpath.c_str(), Core::renderer);

          // TODO: Load other stuff
          chunks[0 + 3 * i] = c;
        }
      }
    }
  }

  // Y
}

void Game::ECS::Systems::Map::draw(SDLW::Renderer* renderer)
{
  int x = 0, y = 0;

  Camera* cs = Manager::get_instance().get_system<Camera>();
  Components::CameraManager* cm = Components::Manager::get_instance().get_component<Components::CameraManager>();
  Components::CameraManager::Instance cmi = cs->get_active_camera();

  // cm_x and cm_y are camera values relative to the current chunk
  int cm_x = cm->get_x(cmi) % 800;
  int cm_y = cm->get_y(cmi) % 800;
  SDL_Rect dest_rect = {0, 0, 800, 800};
  for (int row = 0; row < 3; ++row)
  {
    for (int col = 0; col < 3; ++col)
    {
      SDL_Rect d_rect = dest_rect;
      d_rect.x -= cm_x;
      d_rect.y -= cm_y;
      SDL_RenderCopy(renderer->get_SDL(), chunk_textures[row * 3 + col]->get_SDL(), 0, &d_rect);
      dest_rect.x += 800;
    }
    dest_rect.x = 0;
    dest_rect.y += 800;
  }
}

std::uint32_t Game::ECS::Systems::Map::get_current_chunk() { return current_chunk; }
