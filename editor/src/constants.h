#ifndef SKIDIBIDIBOP_EDITOR_CONSTANTS
#define SKIDIBIDIBOP_EDITOR_CONSTANTS

namespace Editor
{
  namespace Constants
  {
    // Apparently these have to be constexpr rather than const
    constexpr struct
    {
      int width = 960;
      int height = 640;
      int toolBarHeight = 224;
    } Window;

    constexpr struct
    {
      int size = 64;
    } Grid;
  };
};

#endif
