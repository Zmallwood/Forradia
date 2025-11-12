cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCoreAssets ${SOURCES})
target_include_directories(ForradiaCoreAssets PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreAssets
    ForradiaCommonUtilities
    ForradiaCommonGeneral
    ForradiaCommonMatter
)
target_precompile_headers(ForradiaCoreAssets PUBLIC ./src/StdAfx.hpp)
