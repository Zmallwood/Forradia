cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE COMMON_CORE_UTILITIES_SOURCES "./src/*.cpp")
add_library(ForradiaCommonCoreUtilities ${COMMON_CORE_UTILITIES_SOURCES})
target_include_directories(ForradiaCommonCoreUtilities PUBLIC
    "../common_core_utilities/src"
    "../common_general/src"
    "../common_lang/src"
    "../common_matter/src"
)
target_precompile_headers(ForradiaCommonCoreUtilities PUBLIC ./src/StdAfx.hpp)
