#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_CONFIRMATION_STRING
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_CONFIRMATION_STRING

#include <string>
#include "sdlw.h"
#include "confirmation.h"

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Confirmation
    {
      class String : public Base
      {
      public:
        String(const std::string&);
        ~String();

        void input();
        void update();
        void draw();
      private:
        std::string blurb;
        SDLW::Texture* blurb_tex;
        std::string input_text;
        SDLW::Texture* input_text_tex;
        bool update_input_text_tex;
      };
    };
  };
};

#endif
