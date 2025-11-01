cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_GRAPHICS_DEVICES_SOURCES "./src/*.cpp")
add_library(ForradiaCoreGrahicsDevices ${CORE_GRAPHICS_DEVICES_SOURCES})
target_include_directories(ForradiaCoreGrahicsDevices PUBLIC
    "../core_graphics_devices/src"
    "../common_utilities/src"
    "../common_matter/src"
    "../common_lang/src"
    "../common_general/src"
)
target_link_libraries(ForradiaCoreGrahicsDevices ForradiaCommonGeneral assimp)
target_precompile_headers(ForradiaCoreGrahicsDevices PUBLIC ./src/StdAfx.hpp)
