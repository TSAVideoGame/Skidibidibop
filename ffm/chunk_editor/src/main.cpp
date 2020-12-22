#include "window.h"

int main(int argc, char* args[])
{
  const int FPS = 30;
  const int FRAME_DELAY = 1000 / FPS;

  FFM::ChunkEditor::Window::init();

  while (FFM::ChunkEditor::Window::is_running())
  {
    Uint32 frame_start = SDL_GetTicks();

    FFM::ChunkEditor::Window::input();
    FFM::ChunkEditor::Window::update();
    FFM::ChunkEditor::Window::draw();

    int frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time)
    {
      SDL_Delay(FRAME_DELAY - frame_time);
    }
  }

  FFM::ChunkEditor::Window::close();

  return 0;
}
