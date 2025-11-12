cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_RENDERING_SKY_SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingSky ${CORE_RENDERING_SKY_SOURCES})
target_include_directories(ForradiaCoreRenderingSky PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreRenderingSky
    ForradiaCommonLang
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaCoreGraphicsDevices
    ForradiaCoreRenderingCommon
)
target_precompile_headers(ForradiaCoreRenderingSky PUBLIC ./src/StdAfx.hpp)
