cmake_minimum_required(VERSION 3.10)

project(editor)

add_executable(editor
  ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/confirmation/confirmation.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/confirmation/confirmation_bool.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/confirmation/confirmation_string.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/tools/tool.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tools/tool_main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tools/tool_manager.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tools/tool_tab.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tools/tool_tile.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/utility/utility.cpp

  ${CMAKE_CURRENT_LIST_DIR}/src/window/window.cpp
)

# Ignore the /usr/include/SDL2 part, my VIM is messed up :(
target_include_directories(editor PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src/confirmation
  ${CMAKE_CURRENT_LIST_DIR}/src/tools
  ${CMAKE_CURRENT_LIST_DIR}/src/utility
  ${CMAKE_CURRENT_LIST_DIR}/src/window
  ${CMAKE_CURRENT_LIST_DIR}/../data/include
  ${CMAKE_CURRENT_LIST_DIR}/../sdlw/include
  /usr/include/SDL2
)

target_link_directories(editor PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../data/lib
  ${CMAKE_CURRENT_LIST_DIR}/../sdlw/lib
)

target_link_libraries(editor sbbdata sdlw SDL2 SDL2_image SDL2_ttf)

set_target_properties(editor PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
