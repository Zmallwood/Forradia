cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingImages2D ${SOURCES})
target_include_directories(ForradiaCoreRenderingImages2D PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreRenderingImages2D
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaCoreEngine
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
)
target_precompile_headers(ForradiaCoreRenderingImages2D PUBLIC ./src/PCH.hpp)
