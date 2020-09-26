cmake_minimum_required(VERSION 3.10)

project(game)

add_executable(game
  ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/core/core.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/sdl/window.cpp
)

target_include_directories(game PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src/core
  ${CMAKE_CURRENT_LIST_DIR}/src/sdl
)

target_link_libraries(game SDL2 SDL2_image)

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
