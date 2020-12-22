#include "confirmation_string.h"
#include "constants.h"
#include <SDL2/SDL_ttf.h>
#include <cstring>

FFM::ChunkEditor::Confirmation::String::String(const std::string& blurb) : Base()
{
  this->blurb = blurb;
  data->result_type = ResultType::STRING;

  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txt_surface = TTF_RenderText_Blended_Wrapped(font, blurb.c_str(), {0, 0, 0, 0}, 480 - 128);
  blurb_tex = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txt_surface));
  SDL_FreeSurface(txt_surface);
  TTF_CloseFont(font);

  update_input_text_tex = true;

  SDL_StartTextInput();
}

FFM::ChunkEditor::Confirmation::String::~String()
{
  delete blurb_tex;
  delete input_text_tex;

  SDL_StopTextInput();
}

// I'm just basically updating in input because I'm too lazy to make another input struct for key presses :(
void FFM::ChunkEditor::Confirmation::String::input()
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_KEYUP:
      {
        switch (e.key.keysym.sym)
        {
          case SDLK_BACKSPACE:
          {
            if (input_text.length() > 0)
            {
              input_text.pop_back();
              update_input_text_tex = true;
            }
            break;
          }
          case SDLK_RETURN:
          {
            // Need the + sizeof(char) to include the '\0' character
            data->result = malloc(input_text.size() + sizeof(char));
            std::memcpy(data->result, reinterpret_cast<const void*>(input_text.c_str()), input_text.size() + sizeof(char));
            data->size = input_text.size() + sizeof(char);
          }
        }
        break;
      }
      case SDL_TEXTINPUT:
      {
        input_text += e.text.text;
        update_input_text_tex = true;
        break;
      }
    }
  }
}

void FFM::ChunkEditor::Confirmation::String::update()
{
  if (update_input_text_tex)
  {
    TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
    SDL_Surface* txt_surface = TTF_RenderText_Blended_Wrapped(font, input_text.c_str(), {0, 0, 0, 0}, 480 - 128);
    input_text_tex = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txt_surface));
    SDL_FreeSurface(txt_surface);
    TTF_CloseFont(font);
  }
}

void FFM::ChunkEditor::Confirmation::String::draw()
{
  renderer->set_draw_color(255, 255, 255, 255);
  renderer->clear();

  // Draw blurb
  SDL_Rect d_rect = {64, 64, 0, 0};
  SDL_QueryTexture(blurb_tex->get_SDL(), 0, 0, &d_rect.w, &d_rect.h);
  renderer->copy(blurb_tex, 0, &d_rect);

  // Draw blurb
  d_rect = {64, 128, 0, 0};
  SDL_QueryTexture(input_text_tex->get_SDL(), 0, 0, &d_rect.w, &d_rect.h);
  renderer->copy(input_text_tex, 0, &d_rect);

  renderer->present();
}
