cmake_minimum_required(VERSION 3.0)
project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ForradiaCommon
add_library(ForradiaCommon code/common/src/common.cpp)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(ForradiaCommon PRIVATE ${PYTHON_LIBRARIES})
target_link_libraries(ForradiaCommon PRIVATE SDL2 SDL2_image SDL2_ttf fmt GL GLEW)
target_precompile_headers(ForradiaCommon PUBLIC code/common/src/std_afx.hpp)

# ForradiaCore
file(GLOB_RECURSE CORE_SOURCES "code/core/src/*.cpp")
add_library(ForradiaCore ${CORE_SOURCES})
target_include_directories(ForradiaCore PRIVATE "code/common/src")
target_link_libraries(ForradiaCore ForradiaCommon assimp)
target_precompile_headers(ForradiaCore PUBLIC code/core/src/std_afx.hpp)

# ForradiaTheme0WorldStruct
add_library(ForradiaTheme0WorldStruct code/theme_0_world_struct/src/world_struct.cpp)
target_include_directories(ForradiaTheme0WorldStruct PRIVATE "code/common/src")
target_link_libraries(ForradiaTheme0WorldStruct ForradiaCommon)
target_precompile_headers(ForradiaTheme0WorldStruct PUBLIC code/theme_0_world_struct/src/std_afx.hpp)

# ForradiaTheme0
file(GLOB_RECURSE SOURCES "code/theme_0/src/*.cpp")
add_executable(Forradia ${SOURCES})
target_precompile_headers(Forradia PUBLIC code/theme_0/src/std_afx.hpp)
target_include_directories(Forradia PRIVATE
    "code/theme_0/src"
    "code/common/src"
    "code/core/src"
    "code/theme_0_world_struct/src"
)
target_link_libraries(Forradia PRIVATE
    ForradiaCommon
    ForradiaCore
    ForradiaTheme0WorldStruct
)
install(TARGETS Forradia RUNTIME DESTINATION bin)
