#include "confirmation_string.h"
#include "constants.h"
#include <SDL2/SDL_ttf.h>
#include <cstring>

Editor::Confirmation::String::String(const std::string& blurb) : Base()
{
  this->blurb = blurb;
  data->resultType = ResultType::STRING;

  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txtSurface = TTF_RenderText_Blended_Wrapped(font, blurb.c_str(), {0, 0, 0, 0}, 480 - 128);
  blurbTex = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->getSDL(), txtSurface));
  SDL_FreeSurface(txtSurface);
  TTF_CloseFont(font);

  updateInputTextTex = true;

  SDL_StartTextInput();
}

Editor::Confirmation::String::~String()
{
  delete blurbTex;
  delete inputTextTex;

  SDL_StopTextInput();
}

// I'm just basically updating in input because I'm too lazy to make another input struct for key presses :(
void Editor::Confirmation::String::input()
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
            if (inputText.length() > 0)
            {
              inputText.pop_back();
              updateInputTextTex = true;
            }
            break;
          }
          case SDLK_RETURN:
          {
            // Need the + sizeof(char) to include the '\0' character
            data->result = malloc(inputText.size() + sizeof(char));
            std::memcpy(data->result, reinterpret_cast<const void*>(inputText.c_str()), inputText.size() + sizeof(char));
            data->size = inputText.size() + sizeof(char);
          }
        }
        break;
      }
      case SDL_TEXTINPUT:
      {
        inputText += e.text.text;
        updateInputTextTex = true;
        break;
      }
    }
  }
}

void Editor::Confirmation::String::update()
{
  if (updateInputTextTex)
  {
    TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
    SDL_Surface* txtSurface = TTF_RenderText_Blended_Wrapped(font, inputText.c_str(), {0, 0, 0, 0}, 480 - 128);
    inputTextTex = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->getSDL(), txtSurface));
    SDL_FreeSurface(txtSurface);
    TTF_CloseFont(font);
  }
}

void Editor::Confirmation::String::draw()
{
  renderer->set_draw_color(255, 255, 255, 255);
  renderer->clear();

  // Draw blurb
  SDL_Rect dRect = {64, 64, 0, 0};
  SDL_QueryTexture(blurbTex->getSDL(), 0, 0, &dRect.w, &dRect.h);
  renderer->copy(blurbTex, 0, &dRect);

  // Draw blurb
  dRect = {64, 128, 0, 0};
  SDL_QueryTexture(inputTextTex->getSDL(), 0, 0, &dRect.w, &dRect.h);
  renderer->copy(inputTextTex, 0, &dRect);

  renderer->present();
}
