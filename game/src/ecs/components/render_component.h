#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_RENDER_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_RENDER_COMPONENT

#include "sdlw.h"
#include <cstdint>
#include "component.h"
#include "entity.h"
#include "unordered_map"

// TODO
// This is similar to transform component, should make a utilty
// class that can be inherited from
namespace Game
{
  namespace ECS
  {
    namespace Components
    {
      class RenderManager : public Component
      {
      public:
        RenderManager();
        ~RenderManager();

        // All the data is stored in one buffer
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          SDL_Rect* src_rect;
          SDL_Rect* dest_rect;
        };

        // Instance of the component
        struct Instance
        {
          std::uint32_t index;
        };
      private:
        Data data;

        std::unordered_map<Entity, std::uint32_t> map;

        void allocate(std::uint32_t);
      };
    };
  };
};

#endif
