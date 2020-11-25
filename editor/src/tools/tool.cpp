#include "tool.h"
#include <SDL2/SDL_ttf.h>
#include "utility.h"
#include "window.h"

/*
 * ========================================
 * Base tool
 * ========================================
 */
Editor::Tool::Base::Base(SDLW::Renderer* renderer_p, const std::string& text_p, int x_p, int y_p)
{
  renderer = renderer_p;
  text = text_p;
  x = x_p;
  y = y_p;
  destRect = {x_p, y_p, 0, 0};
  texture = Utility::create_text_center(renderer, text, destRect, WIDTH, HEIGHT, {255, 255, 255});
}

Editor::Tool::Base::~Base()
{
  delete texture;
}

void Editor::Tool::Base::draw()
{
  renderer->copy(texture, 0, &destRect);
}

/*
 * ========================================
 * Numeric tool
 *
 * This has numbers and up/down arrows
 * ========================================
 */
Editor::Tool::Numeric::Numeric(SDLW::Renderer* renderer_p, const std::string& text_p, int x_p, int y_p, unsigned int min_p, unsigned int max_p, std::uint16_t* variable_p) : Base(renderer_p, text_p, x_p, y_p)
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

Editor::Tool::Numeric::~Numeric()
{
  for (int i = 0; i < 10; ++i)
    delete number_textures[i];
}

void Editor::Tool::Numeric::draw()
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

bool Editor::Tool::Numeric::hover_increment()
{
  int digits = 6;
  return (Window::get_inputs().mouseX >= x + WIDTH + 16 * digits &&
          Window::get_inputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouseY >= y &&
          Window::get_inputs().mouseY < y + HEIGHT);
}

bool Editor::Tool::Numeric::hover_decrement()
{
  int digits = 6;
  return (Window::get_inputs().mouseX >= x + WIDTH + 16 * digits + HEIGHT &&
          Window::get_inputs().mouseX <= x + WIDTH + 16 * digits + HEIGHT * 2 &&
          Window::get_inputs().mouseY >= y &&
          Window::get_inputs().mouseY < y + HEIGHT);
}

/*
 * ========================================
 * Checkbox tool
 *
 * It do be looking like a radio button though
 * ========================================
 */
Editor::Tool::Checkbox::Checkbox(SDLW::Renderer* renderer_p, const std::string& text_p, int x_p, int y_p, bool* variable_p) : Base(renderer_p, text_p, x_p, y_p)
{
  variable = variable_p;
}

Editor::Tool::Checkbox::~Checkbox()
{

}

void Editor::Tool::Checkbox::draw()
{
  Base::draw();

  // Draw box
  renderer->set_draw_color(255, 255, 255, 255);
  SDL_Rect border = {x + WIDTH + 4, y + 4, HEIGHT - 4, HEIGHT - 4};
  SDL_RenderDrawRect(renderer->get_SDL(), &border);
  
  // Draw fill
  if (*variable)
  {
    SDL_Rect fill = {x + WIDTH + 4 + 8, y + 4 + 8, HEIGHT - 20, HEIGHT - 20};
    SDL_RenderFillRect(renderer->get_SDL(), &fill);
  }
}

bool Editor::Tool::Checkbox::hover()
{
  return (Window::get_inputs().mouseX >= x + WIDTH + 4 &&
          Window::get_inputs().mouseX < x + WIDTH + 4 + (HEIGHT - 4) &&
          Window::get_inputs().mouseY >= y + 4 &&
          Window::get_inputs().mouseY < y + 4 + HEIGHT - 4);
}
