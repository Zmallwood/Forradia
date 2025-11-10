cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_RENDERING_SKY_SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingSky ${CORE_RENDERING_SKY_SOURCES})
target_include_directories(ForradiaCoreRenderingSky PUBLIC
    "../core_rendering/src"
    "../core_rendering_sky/src"
    "../theme_0_properties/src"
    "../common_core_utilities/src"
    "../core_assets/src"
    "../core_rendering_common/src"
    "../theme_0_world_struct/src"
    "../theme_0_essentials/src"
    "../common_matter/src"
)
target_link_libraries(ForradiaCoreRenderingSky
    ForradiaCommonGeneral
    ForradiaCoreGrahicsDevices
)
target_precompile_headers(ForradiaCoreRenderingSky PUBLIC ./src/StdAfx.hpp)
