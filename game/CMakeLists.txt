cmake_minimum_required(VERSION 3.10)

project(game)

# The data stuff should be made into a shared library
add_executable(game
  ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/core/core.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/core/core_object.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/map/map.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/map/tile.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/sdl/renderer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/sdl/texture.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/sdl/window.cpp
)

target_include_directories(game PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src/core
  ${CMAKE_CURRENT_LIST_DIR}/src/map
  ${CMAKE_CURRENT_LIST_DIR}/src/sdl
  ${CMAKE_CURRENT_LIST_DIR}/../data/include
)

target_link_directories(game PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../data/lib
)

target_link_libraries(game sbbdata SDL2 SDL2_image)

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
