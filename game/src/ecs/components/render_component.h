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

        Instance get_instance(const Entity&);

        SDL_Rect get_src_rect(Instance&);
        void     set_src_rect(Instance&, SDL_Rect&);

        SDL_Rect get_dest_rect(Instance&);
        void     set_dest_rect(Instance&, SDL_Rect&);

        Instance add_component(const Entity&);
        void destroy_component(Instance&);
        // TODO: Delete componenet when entity is destroyed
        Data data;
      private:

        std::unordered_map<Entity, std::uint32_t> map;

        void allocate(std::size_t);
      };

      extern Manager::RegisterComponent<RenderManager> render_manager;
    };
  };
};

#endif
