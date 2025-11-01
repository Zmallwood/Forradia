cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE WORLD_STRUCT_SOURCES "./src/*.cpp")
add_library(ForradiaTheme0WorldStruct ${WORLD_STRUCT_SOURCES})
target_include_directories(ForradiaTheme0WorldStruct PUBLIC
    "../theme_0_world_struct/src"
    "../common_utilities/src"
    "../common_core_utilities/src"
    "../common_lang/src"
    "../common_matter/src"
    "../common_general/src"
)
target_link_libraries(ForradiaTheme0WorldStruct ForradiaCommonGeneral)
target_precompile_headers(ForradiaTheme0WorldStruct PUBLIC ./src/StdAfx.hpp)
