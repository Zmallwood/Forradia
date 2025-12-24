cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCoreScenes ${SOURCES})
target_include_directories(ForradiaCoreScenes PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreScenes PRIVATE
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaCoreRenderingImages2D
    ForradiaCoreGUI
)
target_precompile_headers(ForradiaCoreScenes PUBLIC ./src/PCH.hpp)
