cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_GUI_SOURCES "./src/*.cpp")
add_library(ForradiaCoreGUI ${CORE_GUI_SOURCES})
target_include_directories(ForradiaCoreGUI PUBLIC
    "../core_gui/src"
    "../core_graphics_devices/src"
    "../core_rendering/src"
    "../common_lang/src"
    "../common_matter/src"
    "../common_general/src"
    "../common_core_utilities/src"
    "../core_minor_components/src"
    "../core_rendering_base/src"
)
target_precompile_headers(ForradiaCoreGUI PUBLIC ./src/StdAfx.hpp)
target_link_libraries(ForradiaCoreGUI
    ForradiaCoreInput
)