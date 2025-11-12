cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_GUI_SOURCES "./src/*.cpp")
add_library(ForradiaCoreGUI ${CORE_GUI_SOURCES})
target_include_directories(ForradiaCoreGUI PUBLIC
    "./src"
)
target_precompile_headers(ForradiaCoreGUI PUBLIC ./src/StdAfx.hpp)
target_link_libraries(ForradiaCoreGUI
    ForradiaCoreInput
    ForradiaCoreMinorComponents
    ForradiaCoreRenderingColors2D
    ForradiaCoreRenderingText
)