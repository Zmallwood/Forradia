cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_MINOR_COMPONENTS_SOURCES "./src/*.cpp")
add_library(ForradiaCoreMinorComponents ${CORE_MINOR_COMPONENTS_SOURCES})
target_include_directories(ForradiaCoreMinorComponents PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreMinorComponents PRIVATE
    ForradiaCommonLang
    ForradiaCommonMatter
    ForradiaCommonGeneral
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaCoreGraphicsDevices
    ForradiaCoreRenderingImages2D
)
target_precompile_headers(ForradiaCoreMinorComponents PUBLIC ./src/StdAfx.hpp)
