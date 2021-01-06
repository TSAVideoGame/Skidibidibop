#ifndef SKIDIBIDIBOP_GAME_ECS_SYSTEMS_CAMERA_SYSTEM
#define SKIDIBIDIBOP_GAME_ECS_SYSTEMS_CAMERA_SYSTEM

#include "system.h"
#include "sdlw.h"
#include "ffm_data.h"
#include "entity.h"
#include "camera_component.h"
#include <cstdint>
#include <vector>

namespace Game
{
  namespace ECS
  {
    namespace Systems
    {
      class Camera : public System
      {
      public:
        void init();
        static void add_camera(std::uint32_t, int, int);
        static void set_active_camera(std::uint32_t);
        static Components::CameraManager::Instance get_active_camera();
        static void move_camera(int x, int y);
      private:
        static Entity cameras[10]; // std::vector is failing me :(
        static std::uint32_t active_camera; // Index of cameras vector
      };

      extern Manager::RegisterSystem<Camera> camera_system;
    };
  };
};

#endif
