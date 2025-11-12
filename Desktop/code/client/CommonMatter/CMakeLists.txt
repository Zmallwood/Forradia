cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE COMMON_MATTER_SOURCES "./src/*.cpp")
add_library(ForradiaCommonMatter ${COMMON_MATTER_SOURCES})
target_include_directories(ForradiaCommonMatter PUBLIC
    "./src"
)
target_link_libraries(ForradiaCommonMatter PRIVATE
    ForradiaCommonLang
    ForradiaCommonGeneral
)
target_precompile_headers(ForradiaCommonMatter PUBLIC ./src/StdAfx.hpp)
