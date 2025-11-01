cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_RENDERING_BASE_SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingBase ${CORE_RENDERING_BASE_SOURCES})
target_include_directories(ForradiaCoreRenderingBase PUBLIC
    "../core_rendering_base/src"
    "../common_lang/src"
)
target_precompile_headers(ForradiaCoreRenderingBase PUBLIC ./src/StdAfx.hpp)
