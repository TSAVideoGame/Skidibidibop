#include "confirmation_bool.h"
#include "constants.h"
#include <SDL2/SDL_ttf.h>

Editor::Confirmation::Bool::Bool(const std::string& blurb) : Base()
{
  this->blurb = blurb;
  data->resultType = ResultType::BOOL;
  data->size = sizeof(bool);

  TTF_Font* font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 16);
  SDL_Surface* txtSurface = TTF_RenderText_Blended_Wrapped(font, blurb.c_str(), {0, 0, 0, 0}, 480 - 128);
  blurbTex = new SDLW::Texture(SDL_CreateTextureFromSurface(renderer->get_SDL(), txtSurface));
  SDL_FreeSurface(txtSurface);
  TTF_CloseFont(font);
}

Editor::Confirmation::Bool::~Bool()
{
  delete blurbTex;
}

void Editor::Confirmation::Bool::input()
{
  inputs.oldMouseDown = inputs.mouseDown;
  inputs.oldMouseX = inputs.mouseX;
  inputs.oldMouseY = inputs.mouseY;

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
            inputs.mouseDown = true;
            if (!inputs.oldMouseDown)
              SDL_GetMouseState(&inputs.clickMouseX, &inputs.clickMouseY);
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
            inputs.mouseDown = false;
            break;
          }
        }
        break;
      }
    }
  }

SDL_GetMouseState(&inputs.mouseX, &inputs.mouseY);
}

// The boxes
static SDL_Rect yesBox {64, 360 - 64 - 64, 64 * 2, 64};
static SDL_Rect noBox {480 - 64 - 64 * 2, yesBox.y, yesBox.w, yesBox.h};

void Editor::Confirmation::Bool::update()
{
  if (inputs.mouseDown)
  {
    if (inputs.mouseX >= yesBox.x && inputs.mouseX < yesBox.x + yesBox.w && inputs.mouseY >= yesBox.y && inputs.mouseY < yesBox.y + yesBox.h)
    {
      data->result = malloc(sizeof(bool));
      *(reinterpret_cast<bool*>(data->result)) = true;
    }
    if (inputs.mouseX >= noBox.x && inputs.mouseX < noBox.x + noBox.w && inputs.mouseY >= noBox.y && inputs.mouseY < noBox.y + noBox.h)
    {
      data->result = malloc(sizeof(bool));
      *(reinterpret_cast<bool*>(data->result)) = false;
    }
  }
}

void Editor::Confirmation::Bool::draw()
{
  renderer->set_draw_color(255, 255, 255, 255);
  renderer->clear();

  // Draw blurb
  SDL_Rect dRect = {64, 64, 0, 0};
  SDL_QueryTexture(blurbTex->get_SDL(), 0, 0, &dRect.w, &dRect.h);
  renderer->copy(blurbTex, 0, &dRect);

  // Draw yes/no buttons
  renderer->set_draw_color(40, 160, 30, 255);
  SDL_RenderFillRect(renderer->get_SDL(), &yesBox);

  renderer->set_draw_color(245, 45, 45, 255);
  SDL_RenderFillRect(renderer->get_SDL(), &noBox);

  renderer->present();
}
