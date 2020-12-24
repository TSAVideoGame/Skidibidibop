#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_WINDOW_INPUTS
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_WINDOW_INPUTS

namespace FFM
{
  namespace ChunkEditor
  {
    enum class MouseState {HOVER, CLICK, RELEASE, DRAG};

    struct Inputs
    {
      bool old_mouse_down, mouse_down;
      int click_mouse_x, click_mouse_y;
      int old_mouse_x, old_mouse_y;
      int mouse_x, mouse_y, mouse_wheel_y;
      bool up, right, down, left;
    };
  };
};

#endif
