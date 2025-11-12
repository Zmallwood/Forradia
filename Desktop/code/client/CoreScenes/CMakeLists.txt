cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_SCENES_SOURCES "./src/*.cpp")
add_library(ForradiaCoreScenes ${CORE_SCENES_SOURCES})
target_include_directories(ForradiaCoreScenes PUBLIC
    "../core_scenes/src"
    "../core_gui/src"
    "../common_lang/src"
    "../common_matter/src"
    "../common_general/src"
)
target_precompile_headers(ForradiaCoreScenes PUBLIC ./src/StdAfx.hpp)
