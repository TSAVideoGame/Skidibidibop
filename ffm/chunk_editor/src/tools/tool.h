#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_TOOLS_TOOL

#include "sdlw.h"
#include <string>
#include "window_inputs.h"

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

      class Numeric : public Base
      {
      public:
        Numeric(SDLW::Renderer*, const std::string&, int x, int y, unsigned int min, unsigned int max, std::uint16_t* variable);
        virtual ~Numeric();

        virtual void draw();
      protected:
        unsigned int min, max;
        std::uint16_t* variable;
        bool hover_increment();
        bool hover_decrement();
        SDLW::Texture* number_textures[10];
      };
    };
  };
};

#endif
