cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_RENDERING_BASE_SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingCommon ${CORE_RENDERING_BASE_SOURCES})
target_include_directories(ForradiaCoreRenderingCommon PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreRenderingCommon PRIVATE
    ForradiaCommonLang
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaCoreGraphicsDevices
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaTheme0WorldStructure
    ForradiaTheme0Properties
    ForradiaTheme0WorldGeneration
    ForradiaTheme0Essentials
)
target_precompile_headers(ForradiaCoreRenderingCommon PUBLIC ./src/StdAfx.hpp)
