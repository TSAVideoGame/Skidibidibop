cmake_minimum_required(VERSION 3.10)

project(game)

add_executable(game
  ${CMAKE_CURRENT_LIST_DIR}/plugins/plugin.cpp
  ${CMAKE_CURRENT_LIST_DIR}/plugins/audio/audio.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/core/core.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/core/scene.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/ecs/entity.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/ecs/components/component.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/ecs/components/render_component.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/ecs/components/transform_component.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/ecs/systems/render_system.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/ecs/systems/system.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/scenes/test_scene.cpp
)

# Ignore the /usr/include/SDL2 part, my VIM is messed up :(
target_include_directories(game PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/plugins
  ${CMAKE_CURRENT_LIST_DIR}/plugins/audio
  ${CMAKE_CURRENT_LIST_DIR}/plugins/text

  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src/core
  ${CMAKE_CURRENT_LIST_DIR}/src/ecs
  ${CMAKE_CURRENT_LIST_DIR}/src/ecs/components
  ${CMAKE_CURRENT_LIST_DIR}/src/ecs/systems
  ${CMAKE_CURRENT_LIST_DIR}/src/scenes

  ${CMAKE_CURRENT_LIST_DIR}/../data/include
  ${CMAKE_CURRENT_LIST_DIR}/../sdlw/include
  /usr/include/SDL2
)

target_link_directories(game PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../data/lib
  ${CMAKE_CURRENT_LIST_DIR}/../sdlw/lib
)

target_link_libraries(game sbbdata sdlw SDL2 SDL2_mixer)

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
