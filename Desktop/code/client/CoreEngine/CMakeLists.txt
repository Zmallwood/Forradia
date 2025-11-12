cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_ENGINE_SOURCES "./src/*.cpp")
add_library(ForradiaCoreEngine ${CORE_ENGINE_SOURCES})
target_include_directories(ForradiaCoreEngine PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreEngine PRIVATE
    ForradiaCoreInput
    ForradiaCoreRenderingColors2D
    ForradiaCoreRenderingImages2D
    ForradiaCoreRenderingGround
    ForradiaCoreRenderingModels
    ForradiaCoreMinorComponents
    ForradiaCoreScenes
)
target_precompile_headers(ForradiaCoreEngine PUBLIC ./src/StdAfx.hpp)
