cmake_minimum_required(VERSION 3.10)

# Make the shared library
project(sdlw VERSION 0.0.0)

add_library(sdlw SHARED
  ${CMAKE_CURRENT_LIST_DIR}/src/sdlw_renderer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/sdlw_texture.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/sdlw_window.cpp
)

target_include_directories(sdlw PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/../data/include
  /usr/include/SDL2
)

target_link_libraries(sdlw SDL2 SDL2_image)

set_target_properties(sdlw PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY lib
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION}
  PUBLIC_HEADER ${CMAKE_CURRENT_LIST_DIR}/include/sdlw.h
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
