#ifndef SKIDIBIDIBOP_FFM_CHUNK_EDITOR_CONFIRMAITON
#define SKIDIBIDIBOP_FFM_CHUNK_EDITOR_CONFIRMAITON

#include "sdlw.h"
#include "window_inputs.h"

namespace FFM
{
  namespace ChunkEditor
  {
    namespace Confirmation
    {
      enum class ResultType {BOOL, STRING};
      class Base
      {
      public:
        struct Data
        {
          ~Data() { if (result != nullptr) free(result); }
          void* result = nullptr;
          ResultType result_type;
          size_t size;
        };

        Base();
        virtual ~Base();

        virtual void input() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        Data* get_data() { return data; }
      protected:
        SDLW::Window* window;
        SDLW::Renderer* renderer;
        Data* data;
        Inputs inputs;
      };
    };
  };
};

#endif
