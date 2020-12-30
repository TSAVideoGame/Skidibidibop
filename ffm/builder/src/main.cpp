#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>
#include "ffm_data.h"

int main()
{
  std::cout << "FFM Builder\nBuilds the map given chunks\n\n" << std::endl;
  std::cout << "Enter map chunk dimensions (x,y):" << std::endl;

  std::uint8_t x, y;
  std::string dir_path;

  std::cin >> x;
  std::cin >> y;

  std::cout << "Enter the path to the chunks from the cwd" << std::endl;

  std::cin >> dir_path;

  FFM::Data::Types::Chunk null_chunk;

  std::ofstream out_file("map.ffmf", std::ofstream::binary | std::ofstream::trunc);
  std::ofstream out_file_helper("map.ffmfd", std::ofstream::binary | std::ofstream::trunc);
  for (std::uint16_t i = 0; i < x * y; ++i)
  {
    std::ifstream chunkf(dir_path + std::to_string(i % x) + "_" + std::to_string(i / x) + ".ffmc");
    if (chunkf.is_open())
    {
      FFM::Data::Types::Chunk c(chunkf);
      c.save(out_file);
      out_file_helper.write(reinterpret_cast<char*>(&c.size), sizeof(c.size));
    }
    else
    {
      null_chunk.save(out_file);
      out_file_helper.write(reinterpret_cast<char*>(&null_chunk.size), sizeof(null_chunk.size));
    }

    chunkf.close();
  }

  out_file.close();

  return 0;
}
