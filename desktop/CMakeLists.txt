cmake_minimum_required(VERSION 3.0)
project(Forradia)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# ForradiaCommon
add_library(ForradiaCommon src_common/common.cpp)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(ForradiaCommon PRIVATE ${PYTHON_LIBRARIES})
target_link_libraries(ForradiaCommon PRIVATE SDL2 SDL2_image SDL2_ttf fmt GL GLEW)
target_precompile_headers(ForradiaCommon PUBLIC src_common/std_afx.hpp)
# ForradiaCore
file(GLOB_RECURSE CORE_SOURCES "src_core/*.cpp")
add_library(ForradiaCore ${CORE_SOURCES})
target_include_directories(ForradiaCore PRIVATE "src_common")
target_link_libraries(ForradiaCore ForradiaCommon assimp)
target_precompile_headers(ForradiaCore PUBLIC src_core/std_afx.hpp)
# ForradiaTheme0WorldStruct
add_library(ForradiaTheme0WorldStruct src_theme_0_world_struct/world_struct.cpp)
target_include_directories(ForradiaTheme0WorldStruct PRIVATE "src_common")
target_link_libraries(ForradiaTheme0WorldStruct ForradiaCommon)
target_precompile_headers(ForradiaTheme0WorldStruct PUBLIC src_theme_0_world_struct/std_afx.hpp)
# ForradiaTheme0
file(GLOB_RECURSE SOURCES "src_theme_0/*.cpp")
add_executable(Forradia ${SOURCES})
target_precompile_headers(Forradia PUBLIC src_theme_0/std_afx.hpp)
target_include_directories(Forradia PRIVATE
    "src_theme_0"
    "src_common"
    "src_core"
    "src_theme_0_world_struct"
)
target_link_libraries(Forradia PRIVATE
    ForradiaCommon
    ForradiaCore
    ForradiaTheme0WorldStruct
)
install(TARGETS Forradia RUNTIME DESTINATION bin)
