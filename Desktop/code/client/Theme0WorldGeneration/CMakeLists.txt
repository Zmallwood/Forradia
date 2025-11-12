cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE WORLD_GEN_SOURCES "./src/*.cpp")
add_library(ForradiaTheme0WorldGeneration ${WORLD_GEN_SOURCES})
target_include_directories(ForradiaTheme0WorldGeneration PUBLIC
    "./src"
)
target_link_libraries(ForradiaTheme0WorldGeneration PRIVATE
    ForradiaCommonLang
    ForradiaCommonMatter
    ForradiaCommonGeneral
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaTheme0WorldStructure
    ForradiaTheme0Properties
)
target_precompile_headers(ForradiaTheme0WorldGeneration PUBLIC ./src/StdAfx.hpp)
