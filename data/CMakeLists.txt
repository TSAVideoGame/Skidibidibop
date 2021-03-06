cmake_minimum_required(VERSION 3.10)

# Make the shared library
project(sbbdata VERSION 0.0.0)

add_library(sbbdata SHARED
  ${CMAKE_CURRENT_LIST_DIR}/src/data_save.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/data_types.cpp
)

target_include_directories(sbbdata PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/include
)

set_target_properties(sbbdata PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY lib
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION}
  PUBLIC_HEADER ${CMAKE_CURRENT_LIST_DIR}/include/data.h
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make executable tools
project(parser)

add_executable(parser
  ${CMAKE_CURRENT_LIST_DIR}/parser/data_parser.cpp
  ${CMAKE_CURRENT_LIST_DIR}/parser/parser.cpp
)

target_include_directories(parser PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/parser
  ${CMAKE_CURRENT_LIST_DIR}/include
)

set_target_properties(parser PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)


project(builder)

add_executable(builder
  ${CMAKE_CURRENT_LIST_DIR}/builder/data_default_builder.cpp
  ${CMAKE_CURRENT_LIST_DIR}/builder/default_builder.cpp
)

target_include_directories(builder PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/builder
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_directories(builder PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/lib
)

target_link_libraries(builder sbbdata)

set_target_properties(builder PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
