#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_CONFIRMAITON_BOOL
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_CONFIRMAITON_BOOL

#include "confirmation.h"
#include <string>

// Yes / No confirmation
namespace FFM
{
  namespace ChunkEditor
  {
    namespace Confirmation
    {
      class Bool : public Base
      {
      public:
        Bool(const std::string&);
        ~Bool();

        void input();
        void update();
        void draw();
      private:
        std::string blurb;
        SDLW::Texture* blurb_tex;
      };
    };
  };
};

#endif
