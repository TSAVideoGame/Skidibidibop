#include "map_system.h"
#include "core.h"
#include "sdlw.h"
#include <string>

Game::ECS::Systems::Manager::RegisterSystem<Game::ECS::Systems::Map> map_system;

std::vector<FFM::Data::Types::Chunk> Game::ECS::Systems::Map::chunks;
std::uint32_t Game::ECS::Systems::Map::top_left_chunk = 0;

#include <iostream>
void Game::ECS::Systems::Map::update()
{
  // Initialize chunks
  if (chunks.size() == 0)
  {
    for (int row = 0; row < 3; ++row)
      for (int col = 0; col < 3; ++col)
      {
        int chunk_index = row * 3 + col;
        Core::map_file.seekg(Core::map_helper.offsets[chunk_index]);
        FFM::Data::Types::Chunk c(Core::map_file);
        chunks.push_back(c);
        std::cout << "Offset: " << Core::map_helper.offsets[chunk_index] << std::endl;
        std::cout << "Chunk info:" << std::endl;
        std::cout << "Pos: " << c.x << ", " << c.y << std::endl;
        std::cout << "Background: " << c.background_id << std::endl;
        std::cout << "Music: " << c.music_id << std::endl;
        std::cout << "Size: " << c.size() << std::endl;
        std::cout << std::endl;
      }
  }
}

void Game::ECS::Systems::Map::draw(SDLW::Renderer* renderer)
{
  int x = 0, y = 0;

  SDL_Rect dest_rect = {0, 0, 800, 800};
  for (int row = 0; row < 3; ++row)
  {
    for (int col = 0; col < 3; ++col)
    {
      std::string fpath = "res/chunk_images/" + std::to_string(chunks[row * 3 + col].background_id) + ".png";
      SDLW::Texture t(fpath.c_str(), renderer);
      // Super bad, load textures somewhere else, not every frame
      SDL_RenderCopy(renderer->get_SDL(), t.get_SDL(), 0, &dest_rect);
      dest_rect.x += 800;
    }
    dest_rect.y += 800;
  }
}

std::uint32_t Game::ECS::Systems::Map::get_top_left_chunk() { return top_left_chunk; }
