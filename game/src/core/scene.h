#ifndef SKIDIBIDIBOP_GAME_CORE_SCENE
#define SKIDIBIDIBOP_GAME_CORE_SCENE

#include "sdlw.h"
#include <vector>
#include <stdexcept>

namespace Game
{
  namespace Scenes
  {
    /*
     * ========================================
     * Scene
     * ========================================
     */
    class Scene
    {
    public:
      Scene();
      virtual ~Scene();
      virtual void update() = 0;
      virtual void draw(SDLW::Renderer*);
    };

    /*
     * ========================================
     * Void Scene
     *
     * An empty scene
     * ========================================
     */
    class Void : public Scene
    {
    public:
      Void() : Scene() {}
      ~Void() {}
      void update() {}
      void draw(SDLW::Renderer*) {}
    };


    /*
     * ========================================
     * Manager
     *
     * Singleton which manages all the scenes
     * ========================================
     */
    class Manager
    {
    public:
      static Manager& get_instance();

      // TODO: There isn't any transition between the scenes
      void set_scene(Scene*);

      void update();
      void draw(SDLW::Renderer*);

      template <typename T> class RegisterScene
      {
      public:
        RegisterScene()
        {
          static_assert(std::is_base_of<Scene, T>::value, "Scene does not derive from Game::Scene");
          Manager::get_instance().scenes.push_back(new T());
          Manager::get_instance().get_scene<T>(); // This is needed to increment the index
        }
      };

      // Template specialization for Void scene, it just sets it as the current scene
      /*template <> class RegisterScene<Void>
      {
      public:
        RegisterScene()
        {
          Manager::get_instance().scenes.push_back(new Void());
          Manager::get_instance().set_scene(Manager::get_instance().get_scene<Void>());
        }
      };*/

      template <typename T> T* get_scene()
      {
        static std::size_t i = index == scenes.size() - 1 ? index++ : throw std::logic_error("Unregistered Scene");
        return dynamic_cast<T*>(scenes[i]);
      } 
    private:
      Manager();
      ~Manager();

      Scene* current_scene;

      std::size_t index = 0;
      std::vector<Scene*> scenes;
    };

    // Register the void scene
    extern Manager::RegisterScene<Void> void_scene;
  };

};

#endif
