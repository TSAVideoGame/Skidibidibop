#include "tool.h"
#include <SDL2/SDL_ttf.h>
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

/*
 * ========================================
 * Numeric tool
 *
 * This has numbers and up/down arrows
 * ========================================
 */
FFM::ChunkEditor::Tools::Numeric::Numeric(SDLW::Renderer* renderer_p, const std::string& text_p, int x_p, int y_p, unsigned int min_p, unsigned int max_p, std::uint16_t* variable_p) : Base(renderer_p, text_p, x_p, y_p)
{
  min = min_p;
  max = max_p;
  variable = variable_p;

  for (int i = 0; i < 10; ++i)
  {
    TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
    SDL_Surface* txtSurface = TTF_RenderText_Blended(font, std::to_string(i).c_str(), {255, 255, 255});
    number_textures[i] = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txtSurface));
    SDL_FreeSurface(txtSurface);
    TTF_CloseFont(font);
  }
}

FFM::ChunkEditor::Tools::Numeric::~Numeric()
{
  for (int i = 0; i < 10; ++i)
    delete number_textures[i];
}

void FFM::ChunkEditor::Tools::Numeric::draw()
{
  Base::draw();

  // Draw the digits
  int digits = 6;
  for (int i = digits, j = 0; i > 0; --i, ++j)
  {
    int digit = static_cast<int>(*variable / std::pow(10, i - 1)) % 10;
    SDL_Rect dest_rect = {x + WIDTH + 16 * j, y, 0, 0};
    SDL_QueryTexture(number_textures[digit]->get_SDL(), 0, 0, &dest_rect.w, &dest_rect.h);
    dest_rect.y += (HEIGHT - dest_rect.h) / 2;
    renderer->copy(number_textures[digit], 0, &dest_rect);
  }

  // Draw the increase / decrease boxes
  // Points
  SDL_Point upPoints[4] = {
    {x + WIDTH + 16 * digits + 8,              y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + 8 + (HEIGHT - 16) / 2, y   + 8},
    {x + WIDTH + 16 * digits - 8 + HEIGHT,     y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + 8,              y + HEIGHT - 8}
  };
  SDL_Point downPoints[4] = {
    {x + WIDTH + 16 * digits + HEIGHT + 8,                     y          + 8},
    {x + WIDTH + 16 * digits + HEIGHT + 8 + (HEIGHT - 16) / 2, y + HEIGHT - 8},
    {x + WIDTH + 16 * digits + HEIGHT - 8 + HEIGHT,            y          + 8},
    {x + WIDTH + 16 * digits + HEIGHT + 8,                     y          + 8}
  };
  renderer->set_draw_color(255, 255, 255, 255);
  SDL_RenderDrawLines(renderer->get_SDL(), upPoints, 4);
  SDL_RenderDrawLines(renderer->get_SDL(), downPoints, 4);
}

bool FFM::ChunkEditor::Tools::Numeric::hover_increment()
{
  int digits = 6;
  return (Window::get_inputs().mouse_x >= x + WIDTH + 16 * digits &&
          Window::get_inputs().mouse_x <= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouse_y >= y &&
          Window::get_inputs().mouse_y < y + HEIGHT);
}

bool FFM::ChunkEditor::Tools::Numeric::hover_decrement()
{
  int digits = 6;
  return (Window::get_inputs().mouse_x >= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouse_x <= x + WIDTH + 16 * digits + HEIGHT * 2 &&
          Window::get_inputs().mouse_y >= y &&
          Window::get_inputs().mouse_y < y + HEIGHT);
}
