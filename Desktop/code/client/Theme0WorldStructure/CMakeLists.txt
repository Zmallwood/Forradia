cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaTheme0WorldStructure ${SOURCES})
target_include_directories(ForradiaTheme0WorldStructure PUBLIC
    "./src"
)
target_link_libraries(ForradiaTheme0WorldStructure PRIVATE
    ForradiaCommonMatter
    ForradiaCommonGeneral
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaCoreGUI
    ForradiaTheme0Properties
)
target_precompile_headers(ForradiaTheme0WorldStructure PUBLIC ./src/StdAfx.hpp)
