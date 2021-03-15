#ifndef SKIDIBIDIBOP_GAME_ECS_COMPONENTS_ANIMATION_COMPONENT
#define SKIDIBIDIBOP_GAME_ECS_COMPONENTS_ANIMATION_COMPONENT

#include "entity.h"
#include <cstdint>
#include <unordered_map>
#include "component.h"
#include <vector>

namespace Game
{
  namespace ECS
  {
    namespace Components
    {
      /*
       * ========================================
       * Direction Component
       *
       * Has data related to direction
       * ========================================
       */
      class AnimationManager : public Component
      {
      public:
        AnimationManager();
        ~AnimationManager();

        struct AnimationData
        {
          std::uint16_t sprite_id;
          std::uint8_t frames;
        };

        struct Animation
        {
          std::vector<AnimationData> animation_data;
        };

        // All the data is stored in one buffer
        struct Data
        {
          std::uint32_t instances; // Current instances
          std::uint32_t allocated; // Allocated instances
          void* buffer;

          Entity* entity;
          std::uint8_t* state;
          std::uint8_t* frames;
          std::uint8_t* animation_pos;

          // Will use new[] and delete[] instead of being in the buffer
          std::vector<Animation>* animations;
        };

        // An instance of the component
        struct Instance
        {
          std::uint32_t index;
        };

        Instance get_instance(const Entity&);

        std::uint8_t           get_state(Instance&);
        void                   set_state(Instance&, std::uint8_t);

        std::uint8_t           get_frames(Instance&);
        void                   set_frames(Instance&, std::uint8_t);

        std::vector<Animation>  get_animations(Instance&);
        void                    set_animations(Instance&, std::vector<Animation>);
        // Add an animation vector before adding an animation
        void                    add_animation(Instance&, Animation);

        std::uint8_t           get_animation_pos(Instance&);
        void                   set_animation_pos(Instance&, std::uint8_t);

        Instance add_component(const Entity&);
        void destroy_component(Instance&);
        // TODO: Destroy component when entity is destroyed

        Data data;
      private:
        // Given an entity id, this is how we will get the instance index
        std::unordered_map<Entity, std::uint32_t> map;

        void allocate(std::uint32_t);
      };

      // Register the transform component
      extern Manager::RegisterComponent<AnimationManager> animation_manager;
    };
  };
};

#endif
