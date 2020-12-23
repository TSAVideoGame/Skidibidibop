#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL

#include "sdlw.h"
#include <string>
#include <cstring>
#include "window_inputs.h"
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "confirmation_string.h"

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Tools
    {
      class Base
      {
      public:
        static const int WIDTH = 64, HEIGHT = 32;

        Base(SDLW::Renderer*, const std::string&, int x, int y);
        virtual ~Base();

        virtual void update(MouseState) = 0;
        virtual void draw();

        bool is_hovered(const Inputs&);
      protected:
        SDLW::Renderer* renderer;
        std::string text;
        int x, y;
        SDL_Rect dest_rect;
        SDLW::Texture* texture;
      };

      /*
       * ========================================
       * Numeric Tool
       *
       * You should check that T supports the +
       * operator but I don't really want to bother
       * myself at this point
       *
       * I don't want to define it here put it's
       * a template
       *
       * Prepare yourself
       * ========================================
       */
      template <typename T> class Numeric : public Base
      {
      public:
        Numeric(SDLW::Renderer* renderer_p, const std::string& text_p, int x_p, int y_p, T min_p, T max_p, T* variable_p) : Base(renderer_p, text_p, x_p, y_p)
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

        virtual ~Numeric()
        {
          for (int i = 0; i < 10; ++i)
            delete number_textures[i];
        }

        virtual void update(MouseState ms)
        {
          switch (ms)
          {
            case MouseState::CLICK:
            {
              if (hover_increment() && *variable < max)
                ++*variable;

              if (hover_decrement() && *variable > min)
                --*variable;

              if (hover_number())
              {
                Confirmation::String confirm("Enter a number");
                while (confirm.get_data()->result == nullptr)
                {
                  confirm.input();
                  confirm.update();
                  confirm.draw();
                }
                std::size_t length = confirm.get_data()->size;
                char text[length];
                std::strcpy(text, reinterpret_cast<const char*>(confirm.get_data()->result));
                unsigned long long num; // Hopefully this is always big enough
                try
                {
                  num = std::stoull(text);
                  if (num > max || num < min)
                    break;
                }
                catch (const std::exception& e)
                {
                  break;
                }
                *variable = static_cast<T>(num);
              }
              
              break;
            }
          }
        }

        virtual void draw()
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
      protected:
        T min, max;
        T* variable;
        const int digits = 6;
        bool hover_increment()
        {
          return (Window::get_inputs().mouse_x >= x + WIDTH + 16 * digits &&
                  Window::get_inputs().mouse_x <  x + WIDTH + 16 * digits + HEIGHT &&
                  Window::get_inputs().mouse_y >= y &&
                  Window::get_inputs().mouse_y <  y + HEIGHT);
        }

        bool hover_decrement()
        {
          return (Window::get_inputs().mouse_x >= x + WIDTH + 16 * digits + HEIGHT &&
                  Window::get_inputs().mouse_x <  x + WIDTH + 16 * digits + HEIGHT * 2 &&
                  Window::get_inputs().mouse_y >= y &&
                  Window::get_inputs().mouse_y <  y + HEIGHT);
        }

        bool hover_number()
        {
          return (Window::get_inputs().mouse_x >= x + WIDTH &&
                  Window::get_inputs().mouse_x <  x + WIDTH + 16 * digits &&
                  Window::get_inputs().mouse_y >= y &&
                  Window::get_inputs().mouse_y <  y + HEIGHT);
        }
        SDLW::Texture* number_textures[10];
      };
    };
  };
};

#endif
