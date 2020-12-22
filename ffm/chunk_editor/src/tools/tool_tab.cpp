#include "tool_tab.h"
#include "utility.h"
#include "tool_main.h"
#include "tool_objects.h"

/*
 * ========================================
 * Tab
 *
 * Oragnizes tools
 * ========================================
 */
FFM::ChunkEditor::Tools::Tab::Tab(SDLW::Renderer* renderer_p, const std::string& text_p, int x_p, int y_p, SDL_Color color_p)
{
  text = text_p;
  x = x_p;
  y = y_p;
  color = color_p;
  renderer = renderer_p;
  dest_rect = {0, 0, 64, 32}; // Dest Rect of texture with text on it
  texture = Utility::create_text_center(renderer, text, dest_rect, 64, 32, {255, 255, 255});
  is_selected = false;
}

FFM::ChunkEditor::Tools::Tab::~Tab()
{
  delete texture;

  for (Base* t : tools)
    delete t;
}

void FFM::ChunkEditor::Tools::Tab::update(MouseState ms)
{
  if (is_selected)
  {
    for (Base* t : tools)
      t->update(ms);
  }
}

void FFM::ChunkEditor::Tools::Tab::draw()
{
  // Draw self
  renderer->set_draw_color(color.r, color.g, color.b, 255);
  SDL_Rect fill_rect = {x + 4, y + 4, 24, 24};
  SDL_RenderFillRect(renderer->get_SDL(), &fill_rect);
  
  // Draw if active
  if (is_selected)
  {
    SDL_Rect fill_rect = {0, 0, 64, 32};
    SDL_RenderFillRect(renderer->get_SDL(), &fill_rect);
    renderer->copy(texture, 0, &dest_rect);

    for (Base* t : tools)
      t->draw();
  }
}

bool FFM::ChunkEditor::Tools::Tab::is_hovered(int mx, int my)
{
  return mx >= x && mx <= x + 32 && my >= y && my <= y + 32;
}

/*
 * ========================================
 * Predefined Tabs
 * ========================================
 */
FFM::ChunkEditor::Tools::Tabs::Main::Main(SDLW::Renderer* renderer, int x, int y) : Tab(renderer, "Main", x, y, {20, 20, 20})
{
  tools.reserve(4);

  tools.push_back(new Tools::Main::Save(renderer, 16, (16 + 32) * 1));
  tools.push_back(new Tools::Main::Load(renderer, 16, (16 + 32) * 2));
  tools.push_back(new Tools::Main::PosX(renderer, 16, (16 + 32) * 3));
  tools.push_back(new Tools::Main::PosY(renderer, 16, (16 + 32) * 4));
}

FFM::ChunkEditor::Tools::Tabs::Objects::Objects(SDLW::Renderer* renderer, int x, int y) : Tab(renderer, "Objs", x, y, {255, 180, 10})
{
  tools.reserve(2);

  tools.push_back(new Tools::Objects::Edit::Main(renderer, 16, (16 + 32) * 1));
  tools.push_back(new Tools::Objects::Images    (renderer, 16, (16 + 32) * 3));
}
