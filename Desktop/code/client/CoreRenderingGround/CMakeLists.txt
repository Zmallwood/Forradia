cmake_minimum_required(VERSION 3.0)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE CORE_RENDERING_GROUND_SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingGround ${CORE_RENDERING_GROUND_SOURCES})
target_include_directories(ForradiaCoreRenderingGround PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreRenderingGround
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
target_precompile_headers(ForradiaCoreRenderingGround PUBLIC ./src/StdAfx.hpp)
