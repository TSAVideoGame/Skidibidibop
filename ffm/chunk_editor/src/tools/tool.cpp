#include "tool.h"
#include "utility.h"
#include "window.h"

/*
 * ====================================
 * Base Tool
 * ====================================
 */
FFM::ChunkEditor::Tools::Base::Base(SDLW::Renderer* renderer_p, const std::string& text_p, int x_p, int y_p)
{
  renderer = renderer_p;
  text = text_p;
  x = x_p;
  y = y_p;
  dest_rect = {x_p, y_p, 0, 0};
  texture = Utility::create_text_center(renderer, text, dest_rect, WIDTH, HEIGHT, {255, 255, 255});
}

FFM::ChunkEditor::Tools::Base::~Base()
{
  delete texture;
}

void FFM::ChunkEditor::Tools::Base::draw()
{
  renderer->copy(texture, 0, &dest_rect);
}

bool FFM::ChunkEditor::Tools::Base::is_hovered(const Inputs& i)
{
  return i.mouse_x >= x && i.mouse_x < x + WIDTH && i.mouse_y >= y && i.mouse_y < y + HEIGHT; 
}
