#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>
#include "ffm_data.h"

int main(int argc, char* args[])
{
  if (argc > 1)
  {
    // DEBUG MODE
    // Makes a debug map
    //
    // Contains nothing except incrementing background ids

    std::ofstream out_file("map.ffmf", std::ofstream::binary | std::ofstream::trunc);
    std::ofstream out_file_helper("map.ffmfd", std::ofstream::binary | std::ofstream::trunc);
   
    int x = 9, y = 9;

    FFM::Data::Types::Map map;
    map.offsets.reserve(x * y + 1);
    map.offsets.push_back(0);
    map.x = x;
    map.y = y;

    for (std::uint32_t i = 0; i < x * y; ++i)
    {
      FFM::Data::Types::Chunk c;
      c.background_id = i + 1;
      c.save(out_file);
      
      map.offsets.push_back(map.offsets[i] + c.size());
    }

    map.offsets.erase(map.offsets.end() - 1); // There will be an extra offset
    map.save(out_file_helper);
      
    out_file.close();
    out_file_helper.close();
    
    return 1;
  }

  std::cout << "FFM Builder\nBuilds the map given chunks\n\n" << std::endl;
  std::cout << "Enter map chunk dimensions (x,y):" << std::endl;

  std::uint16_t x, y;
  std::string dir_path;

  std::cin >> x;
  std::cin >> y;

  std::cout << "Enter the path to the chunks from the cwd" << std::endl;

  std::cin >> dir_path;

  FFM::Data::Types::Chunk null_chunk;

  std::ofstream out_file("map.ffmf", std::ofstream::binary | std::ofstream::trunc);
  std::ofstream out_file_helper("map.ffmfd", std::ofstream::binary | std::ofstream::trunc);
  
  FFM::Data::Types::Map map;
  map.offsets.reserve(x * y + 1);
  map.offsets.push_back(0);
  map.x = x;
  map.y = y;
 
  for (std::uint16_t i = 0; i < x * y; ++i)
  {
    std::ifstream chunkf(dir_path + std::to_string(i % x) + "_" + std::to_string(i / x) + ".ffmc");
    if (chunkf.is_open())
    {
      FFM::Data::Types::Chunk c(chunkf);
      c.save(out_file);
      map.offsets.push_back(map.offsets[i] + c.size());
    }
    else
    {
      null_chunk.save(out_file);
      map.offsets.push_back(map.offsets[i] + null_chunk.size());
    }

    chunkf.close();
  }
  
  map.offsets.erase(map.offsets.end() - 1); // There will be an extra offset
  map.save(out_file_helper);

  out_file.close();
  out_file_helper.close();

  return 0;
}
