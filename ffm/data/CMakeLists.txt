cmake_minimum_required(VERSION 3.10)

project(ffmdata VERSION 0.0.0)

add_library(ffmdata SHARED
  ${CMAKE_CURRENT_LIST_DIR}/src/ffm_data_types.cpp
)

# Ignore the /usr/include/SDL2 part, my VIM is messed up :(
target_include_directories(ffmdata PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
  /usr/include/SDL2
)

target_link_libraries(ffmdata)

set_target_properties(ffmdata PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY lib
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION}
  PUBLIC_HEADER ${CMAKE_CURRENT_LIST_DIR}/include/ffm_data.h
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
