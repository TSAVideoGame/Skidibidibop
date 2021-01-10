#include "map_system.h"
#include "core.h"
#include "sdlw.h"
#include "camera_system.h"
#include "camera_component.h"
#include <string>

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Map> map_system;

std::vector<FFM::Data::Types::Chunk> Game::ECS::Systems::Map::chunks;
std::uint32_t Game::ECS::Systems::Map::top_left_chunk = 0;
// Everything involving this (below) is mad sus and dodgy
std::vector<SDLW::Texture*> Game::ECS::Systems::Map::chunk_textures;

#include <iostream>
void Game::ECS::Systems::Map::update()
{
  // Initialize chunks
  if (chunks.size() == 0)
  {
    // Sets 0,0 as the center of the three chunks (first row and column are null chunks)
    for (int row = -1; row < 2; ++row)
      for (int col = -1; col < 2; ++col)
      {
        int chunk_index = row * 3 + col;
        if (row < 0 || col < 0)
          chunk_index = -1;

        FFM::Data::Types::Chunk c;
        if (chunk_index >= 0 && chunk_index < Core::map_helper.num_chunks)
        {
          std::cout << "Loaded chunk" << std::endl;
          Core::map_file.seekg(Core::map_helper.offsets[chunk_index]);
          c.load(Core::map_file);
        }
        chunks.push_back(c);

        std::string fpath = "res/chunk_images/" + std::to_string(c.background_id) + ".png";
        std::cout << chunk_index << std::endl;
        chunk_textures.push_back(new SDLW::Texture(fpath.c_str(), Core::renderer));
        // Last two initial chunks have incorrect backgrounds
        std::cout << "Error: " << c.background_id << std::endl;
        SDL_RenderCopy(Core::renderer->get_SDL(), SDLW::Texture(fpath.c_str(), Core::renderer).get_SDL(), 0, 0);
      }
  }
}

void Game::ECS::Systems::Map::draw(SDLW::Renderer* renderer)
{
  int x = 0, y = 0;

  Camera* cs = Manager::get_instance().get_system<Camera>();
  Components::CameraManager* cm = Components::Manager::get_instance().get_component<Components::CameraManager>();
  Components::CameraManager::Instance cmi = cs->get_active_camera();

  SDL_Rect dest_rect = {-800, -800, 800, 800};
  for (int row = 0; row < 3; ++row)
  {
    for (int col = 0; col < 3; ++col)
    {
      SDL_Rect d_rect = dest_rect;
      d_rect.x -= cm->get_x(cmi);
      d_rect.y -= cm->get_y(cmi);
      SDL_RenderCopy(renderer->get_SDL(), chunk_textures[row * 3 + col]->get_SDL(), 0, &d_rect);
      dest_rect.x += 800;
    }
    dest_rect.x = -800;
    dest_rect.y += 800;
  }
}

std::uint32_t Game::ECS::Systems::Map::get_top_left_chunk() { return top_left_chunk; }
