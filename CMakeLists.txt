cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("src")

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Forradia ${SOURCES})

target_link_libraries(Forradia PRIVATE SDL2 SDL2_image SDL2_ttf fmt)

target_precompile_headers(Forradia PRIVATE src/std_afx.hpp)

install(TARGETS Forradia RUNTIME DESTINATION bin)
