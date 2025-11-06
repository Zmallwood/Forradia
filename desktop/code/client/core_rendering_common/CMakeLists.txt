cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_RENDERING_BASE_SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingCommon ${CORE_RENDERING_BASE_SOURCES})
target_include_directories(ForradiaCoreRenderingCommon PUBLIC
    "../core_rendering_common/src"
    "../common_lang/src"
    "../common_general/src"
    "../theme_0_world_struct/src"
    "../theme_0_essentials/src"
    "../theme_0_properties/src"
    "../common_matter/src"
)
target_link_libraries(ForradiaCoreRenderingCommon PRIVATE
    ForradiaCoreGrahicsDevices
    ForradiaCommonCoreUtilities
)
target_precompile_headers(ForradiaCoreRenderingCommon PUBLIC ./src/StdAfx.hpp)
