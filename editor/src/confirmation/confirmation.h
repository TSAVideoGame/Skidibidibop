#ifndef SKIDIBIDIBOP_EDITOR_CONFIRMAITON
#define SKIDIBIDIBOP_EDITOR_CONFIRMAITON

#include "sdlw.h"
#include "window_inputs.h"

namespace Editor
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
        ResultType resultType;
        size_t size;
      };

      Base();
      virtual ~Base();

      virtual void input() = 0;
      virtual void update() = 0;
      virtual void draw() = 0;

      Data* getData() { return data; }
    protected:
      SDLW::Window* window;
      SDLW::Renderer* renderer;
      Data* data;
      Uint32 windowID;
      Inputs inputs;
    };
  };
};

#endif
