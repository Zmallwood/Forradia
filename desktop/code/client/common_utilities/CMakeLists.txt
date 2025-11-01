cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE COMMON_UTILITIES_SOURCES "./src/*.cpp")
add_library(ForradiaCommonUtilities ${COMMON_UTILITIES_SOURCES})
target_include_directories(ForradiaCommonUtilities PUBLIC
    "../common_utilities/src"
    "../common_lang/src"
)
target_precompile_headers(ForradiaCommonUtilities PUBLIC ./src/StdAfx.hpp)
