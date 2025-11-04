cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_ENGINE_SOURCES "./src/*.cpp")
add_library(ForradiaCoreEngine ${CORE_ENGINE_SOURCES})
target_include_directories(ForradiaCoreEngine PUBLIC
    "../core_engine/src"
    "../core_graphics_devices/src"
    "../core_rendering/src"
    "../core_scenes/src"
    "../core_input/src"
    "../common_lang/src"
    "../common_matter/src"
    "../common_utilities/src"
    "../common_general/src"
    "../core_minor_components/src"
    "../core_rendering_common/src"
    "../core_rendering_ground/src"
    "../core_rendering_images_2d/src"
    "../core_rendering_models/src"
)
target_precompile_headers(ForradiaCoreEngine PUBLIC ./src/StdAfx.hpp)
