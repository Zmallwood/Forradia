cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_SCENES_SOURCES "./src/*.cpp")
add_library(ForradiaCoreScenes ${CORE_SCENES_SOURCES})
target_include_directories(ForradiaCoreScenes PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreScenes PRIVATE
    ForradiaCommonLang
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaCoreRenderingImages2D
    ForradiaCoreGUI
)
target_precompile_headers(ForradiaCoreScenes PUBLIC ./src/StdAfx.hpp)
