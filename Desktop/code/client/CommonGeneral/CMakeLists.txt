cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCommonGeneral ${SOURCES})
target_include_directories(ForradiaCommonGeneral PUBLIC
    "./src"
)
target_link_libraries(ForradiaCommonGeneral PRIVATE
    ForradiaCommonLang
    ForradiaCommonMatter
    SDL2
    SDL2_image
    SDL2_ttf
    fmt
    GL
    GLEW
)
target_precompile_headers(ForradiaCommonGeneral PUBLIC ./src/StdAfx.hpp)