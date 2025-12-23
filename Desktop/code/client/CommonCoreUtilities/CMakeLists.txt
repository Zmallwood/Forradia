cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCommonCoreUtilities ${SOURCES})
target_include_directories(ForradiaCommonCoreUtilities PUBLIC
    "./src"
)
target_link_libraries(ForradiaCommonCoreUtilities PUBLIC
    ForradiaCommonUtilities
    ForradiaCommonMatter
)
target_precompile_headers(ForradiaCommonCoreUtilities PUBLIC ./src/StdAfx.hpp)
