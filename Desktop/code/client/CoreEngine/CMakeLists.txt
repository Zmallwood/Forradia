cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCoreEngine ${SOURCES})
target_include_directories(ForradiaCoreEngine PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreEngine PRIVATE
    ForradiaCoreRenderingColors2D
    ForradiaCoreRenderingImages2D
    ForradiaCoreRenderingGround
    ForradiaCoreRenderingModels
    ForradiaCoreRenderingText
    ForradiaTheme0Essentials
    assimp
)
target_precompile_headers(ForradiaCoreEngine PUBLIC ./src/PCH.hpp)
