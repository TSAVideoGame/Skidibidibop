#include "confirmation.h"
#include "window.h"

FFM::ChunkEditor::Confirmation::Base::Base() :
  inputs({false, false, 0, 0, 0, 0, 0, 0, 0})
{
  window = new SDLW::Window("Confirm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 320, 0);
  renderer = new SDLW::Renderer(window);

  data = new Data;
}

FFM::ChunkEditor::Confirmation::Base::~Base()
{
  delete data;
  delete renderer;
  delete window;
}
