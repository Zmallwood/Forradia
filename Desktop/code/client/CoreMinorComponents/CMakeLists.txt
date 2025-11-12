cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_MINOR_COMPONENTS_SOURCES "./src/*.cpp")
add_library(ForradiaCoreMinorComponents ${CORE_MINOR_COMPONENTS_SOURCES})
target_include_directories(ForradiaCoreMinorComponents PUBLIC
    "../core_minor_components/src"
    "../core_graphics_devices/src"
    "../core_rendering/src"
    "../common_lang/src"
    "../common_matter/src"
    "../common_general/src"
    "../common_core_utilities/src"
    "../core_rendering_common/src"
    "../core_rendering_images_2d/src"
)
target_precompile_headers(ForradiaCoreMinorComponents PUBLIC ./src/StdAfx.hpp)
