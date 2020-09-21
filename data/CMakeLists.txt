cmake_minimum_required(VERSION 3.10)

project(parser)

add_executable(parser
  ${CMAKE_CURRENT_LIST_DIR}/src/tester.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/data_parser.cpp
)

target_include_directories(parser PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
)

set_target_properties(parser PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
