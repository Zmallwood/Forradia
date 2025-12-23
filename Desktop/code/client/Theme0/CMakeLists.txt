cmake_minimum_required(VERSION 3.5)

project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "./src/*.cpp")
add_executable(Forradia ${SOURCES})
#target_link_libraries(Forradia PRIVATE )
target_precompile_headers(Forradia PUBLIC ./src/StdAfx.hpp)
target_include_directories(Forradia PUBLIC
    "./src"
)
target_link_libraries(Forradia PRIVATE
    ForradiaCommonGeneral
    ForradiaCoreRenderingImages2D
    ForradiaCoreRenderingText
    ForradiaCoreRenderingGround
    ForradiaCoreRenderingModels
    ForradiaTheme0WorldStructure
    ForradiaTheme0WorldGenerationMain
    ForradiaTheme0Essentials
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaCoreAssets
    ForradiaCoreGUI
    ForradiaCoreScenes
    ForradiaCoreEngine
    ForradiaTheme0Properties
    ForradiaCoreMinorComponents
    ForradiaCoreRenderingCommon
    ForradiaCoreRenderingColors2D
    ForradiaCoreRenderingSky
    ForradiaTheme0Core
    ForradiaTheme0CustomGUI
    ForradiaTheme0Scenes
)

file(COPY ${CMAKE_SOURCE_DIR}/../Resources
        DESTINATION ${CMAKE_BINARY_DIR}/client/Theme0)