cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaTheme0WorldGenerationGround ${SOURCES})
target_include_directories(ForradiaTheme0WorldGenerationGround PUBLIC
    "./src"
)
target_link_libraries(ForradiaTheme0WorldGenerationGround PRIVATE
    ForradiaCommonMatter
    ForradiaCommonGeneral
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaTheme0WorldStructure
    ForradiaTheme0Properties
    ForradiaTheme0WorldGenerationCommon
)
target_precompile_headers(ForradiaTheme0WorldGenerationGround PUBLIC ./src/StdAfx.hpp)
