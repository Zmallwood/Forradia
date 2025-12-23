cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCoreMinorComponents ${SOURCES})
target_include_directories(ForradiaCoreMinorComponents PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreMinorComponents PRIVATE
    ForradiaCommonMatter
    ForradiaCommonGeneral
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaCoreGraphicsDevices
    ForradiaCoreRenderingImages2D
)
target_precompile_headers(ForradiaCoreMinorComponents PUBLIC ./src/StdAfx.hpp)
