#include "confirmation_bool.h"
#include "constants.h"
#include <SDL2/SDL_ttf.h>

FFM::ChunkEditor::Confirmation::Bool::Bool(const std::string& blurb) : Base()
{
  this->blurb = blurb;
  data->result_type = ResultType::BOOL;
  data->size = sizeof(bool);

  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txt_surface = TTF_RenderText_Blended_Wrapped(font, blurb.c_str(), {0, 0, 0, 0}, 480 - 128);
  blurb_tex = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txt_surface));
  SDL_FreeSurface(txt_surface);
  TTF_CloseFont(font);
}

FFM::ChunkEditor::Confirmation::Bool::~Bool()
{
  delete blurb_tex;
}

void FFM::ChunkEditor::Confirmation::Bool::input()
{
  inputs.old_mouse_down = inputs.mouse_down;
  inputs.old_mouse_x = inputs.mouse_x;
  inputs.old_mouse_y = inputs.mouse_y;

  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_MOUSEBUTTONDOWN:
      {
        switch (e.button.button)
        {
          case SDL_BUTTON_LEFT:
          {
            inputs.mouse_down = true;
            if (!inputs.old_mouse_down)
              SDL_GetMouseState(&inputs.click_mouse_x, &inputs.click_mouse_y);
            break;
          }
        }
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        switch (e.button.button)
        {
          case SDL_BUTTON_LEFT:
          {
            inputs.mouse_down = false;
            break;
          }
        }
        break;
      }
    }
  }

SDL_GetMouseState(&inputs.mouse_x, &inputs.mouse_y);
}

// The boxes
static SDL_Rect yes_box {64, 360 - 64 - 64, 64 * 2, 64};
static SDL_Rect no_box {480 - 64 - 64 * 2, yes_box.y, yes_box.w, yes_box.h};

void FFM::ChunkEditor::Confirmation::Bool::update()
{
  if (inputs.mouse_down)
  {
    if (inputs.mouse_x >= yes_box.x && inputs.mouse_x < yes_box.x + yes_box.w && inputs.mouse_y >= yes_box.y && inputs.mouse_y < yes_box.y + yes_box.h)
    {
      data->result = malloc(sizeof(bool));
      *(reinterpret_cast<bool*>(data->result)) = true;
    }
    if (inputs.mouse_x >= no_box.x && inputs.mouse_x < no_box.x + no_box.w && inputs.mouse_y >= no_box.y && inputs.mouse_y < no_box.y + no_box.h)
    {
      data->result = malloc(sizeof(bool));
      *(reinterpret_cast<bool*>(data->result)) = false;
    }
  }
}

void FFM::ChunkEditor::Confirmation::Bool::draw()
{
  renderer->set_draw_color(255, 255, 255, 255);
  renderer->clear();

  // Draw blurb
  SDL_Rect d_rect = {64, 64, 0, 0};
  SDL_QueryTexture(blurb_tex->get_SDL(), 0, 0, &d_rect.w, &d_rect.h);
  renderer->copy(blurb_tex, 0, &d_rect);

  // Draw yes/no buttons
  renderer->set_draw_color(40, 160, 30, 255);
  SDL_RenderFillRect(renderer->get_SDL(), &yes_box);

  renderer->set_draw_color(245, 45, 45, 255);
  SDL_RenderFillRect(renderer->get_SDL(), &no_box);

  renderer->present();
}
