#include "tool.h"
#include "tool_main.h"
#include "tool_tile.h"
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "window.h"
#include "utility.h"

Editor::Tool::Tab::Tab(SDLW::Renderer* renderer_p, const std::string& text_p, int x_p, int y_p, SDL_Color color_p)
{
  text = text_p;
  x = x_p;
  y = y_p;
  color = color_p;
  renderer = renderer_p;
  dest_rect = {x_p, y_p, 64, 32};
  texture = Utility::create_text_center(renderer, text, dest_rect, 64, 32, {255, 255, 255});
  isSelected = false;
}

Editor::Tool::Tab::~Tab()
{
  for (Base* t : tools)
    delete t;

  tools.clear();
}

void Editor::Tool::Tab::update(MouseState ms)
{
  if (isSelected)
  {
    for (Base* t : tools)
      t->update(ms);
  }
}

void Editor::Tool::Tab::draw()
{
  // Draw self
  renderer->set_draw_color(color.r, color.g, color.b, 255);
  SDL_Rect fill_rect = {x, y, 64, 32};
  SDL_RenderFillRect(renderer->get_SDL(), &fill_rect);
  renderer->copy(texture, 0, &dest_rect);

  if (isSelected)
  {
    // Draw tools
    for (Base* t : tools)
      t->draw();
  }
}

bool Editor::Tool::Tab::isHovered(int mx, int my)
{
  return mx >= x && mx <= x + 64 && my >= y && my <= y + 32; 
}

// Main tab
Editor::Tool::Tabs::Main::Main(SDLW::Renderer* renderer, const std::string& text, int x, int y, SDL_Color color) : Tab(renderer, text, x, y, color)
{
  tools.push_back(new Tool::Main::Save(renderer, 0, Constants::Window.height - Constants::Window.toolBarHeight));
  tools.push_back(new Tool::Main::Load(renderer, 0, Constants::Window.height - Constants::Window.toolBarHeight + Base::HEIGHT * 1));
}

// Tile tab
Editor::Tool::Tabs::Tile::Tile(SDLW::Renderer* renderer, const std::string& text, int x, int y, SDL_Color color) : Tab(renderer, text, x, y, color)
{
  tools.push_back(new Tool::Tile::Col(renderer, 0, Constants::Window.height - Constants::Window.toolBarHeight));
  tools.push_back(new Tool::Tile::Row(renderer, 0, Constants::Window.height - Constants::Window.toolBarHeight + Base::HEIGHT * 1));
  tools.push_back(new Tool::Tile::Edit::Main(renderer, 0, Constants::Window.height - Constants::Window.toolBarHeight + Base::HEIGHT * 2));
}
