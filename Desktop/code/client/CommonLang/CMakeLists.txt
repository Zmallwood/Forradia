 
cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE COMMON_LANG_SOURCES "./src/*.cpp")
add_library(ForradiaCommonLang INTERFACE)
target_sources(ForradiaCommonLang INTERFACE ${COMMON_LANG_SOURCES})
target_include_directories(ForradiaCommonLang INTERFACE
    "./src"
)
target_precompile_headers(ForradiaCommonLang INTERFACE ./src/StdAfx.hpp)