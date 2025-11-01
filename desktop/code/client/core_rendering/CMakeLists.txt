cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_RENDERING_SOURCES "./src/*.cpp")
add_library(ForradiaCoreRendering ${CORE_RENDERING_SOURCES})
target_include_directories(ForradiaCoreRendering PUBLIC
    "../core_rendering/src"
    "../theme_0_properties/src"
    "../common_core_utilities/src"
    "../core_assets/src"
    "../core_rendering_base/src"
)
target_link_libraries(ForradiaCoreRendering
    ForradiaCommonGeneral
    ForradiaCoreGrahicsDevices
    assimp
)
target_precompile_headers(ForradiaCoreRendering PUBLIC ./src/StdAfx.hpp)
