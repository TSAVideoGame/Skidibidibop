#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_CONSTANTS
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_CONSTANTS

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Constants
    {
      constexpr struct
      {
        int X_TILES = 25, Y_TILES = 25;
        int TILE_SIZE = 32; // Size in pixels 
      } Chunk;

      constexpr struct
      {
        int TOOL_WIDTH = 256;
        //int TOOL_HEIGHT = 0;
        int VIEW_WIDTH = Chunk.TILE_SIZE * Chunk.X_TILES;
        int VIEW_HEIGHT = Chunk.TILE_SIZE * Chunk.Y_TILES;
      } Window;
    };
  };
};

#endif
