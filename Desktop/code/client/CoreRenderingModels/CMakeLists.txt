cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingModels ${SOURCES})
target_include_directories(ForradiaCoreRenderingModels PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreRenderingModels
    ForradiaCommonLang
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaCoreGraphicsDevices
    ForradiaCoreAssets
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaCoreRenderingCommon
    ForradiaTheme0Properties
)
target_precompile_headers(ForradiaCoreRenderingModels PUBLIC ./src/StdAfx.hpp)
