cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_library(ForradiaCoreRenderingGround ${SOURCES})
target_include_directories(ForradiaCoreRenderingGround PUBLIC
    "./src"
)
target_link_libraries(ForradiaCoreRenderingGround
    ForradiaCommonGeneral
    ForradiaCommonMatter
    ForradiaCoreEngine
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaCoreRenderingCommon
    ForradiaTheme0Properties
)
target_precompile_headers(ForradiaCoreRenderingGround PUBLIC ./src/PCH.hpp)
