cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingColors2D ${SOURCES})
target_include_directories(ForradiaCoreRenderingColors2D PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreRenderingColors2D
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaCoreEngine
    ForradiaCoreRenderingCommon
)
target_precompile_headers(ForradiaCoreRenderingColors2D PUBLIC ./src/PCH.hpp)
