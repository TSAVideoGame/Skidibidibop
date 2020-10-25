#ifndef SKIDIBIDIBOP_EDITOR_CONFIRMATION_STRING
#define SKIDIBIDIBOP_EDITOR_CONFIRMATION_STRING

#include <string>
#include "sdlw.h"
#include "confirmation.h"

namespace Editor
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
      SDLW::Texture* blurbTex;
      std::string inputText;
      SDLW::Texture* inputTextTex;
      bool updateInputTextTex;
    };
  };
};

#endif
