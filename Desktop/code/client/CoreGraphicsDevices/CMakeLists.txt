cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_GRAPHICS_DEVICES_SOURCES "./src/*.cpp")
add_library(ForradiaCoreGraphicsDevices ${CORE_GRAPHICS_DEVICES_SOURCES})
target_include_directories(ForradiaCoreGraphicsDevices PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreGraphicsDevices PRIVATE
    ForradiaCommonLang
    ForradiaCommonMatter
    ForradiaCommonGeneral
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    assimp
)
target_precompile_headers(ForradiaCoreGraphicsDevices PUBLIC ./src/StdAfx.hpp)
