cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_RENDERING_TEXT_SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingText ${CORE_RENDERING_TEXT_SOURCES})
target_include_directories(ForradiaCoreRenderingText PUBLIC
    "../core_rendering/src"
    "../theme_0_properties/src"
    "../common_core_utilities/src"
    "../core_assets/src"
    "../core_rendering_common/src"
    "../core_rendering_images_2d/src"
    "../theme_0_world_struct/src"
    "../theme_0_essentials/src"
    "../common_matter/src"
    "../common_general/src"
)
target_link_libraries(ForradiaCoreRenderingText
    ForradiaCommonGeneral
    ForradiaCoreGrahicsDevices
)
target_precompile_headers(ForradiaCoreRenderingText PUBLIC ./src/StdAfx.hpp)
