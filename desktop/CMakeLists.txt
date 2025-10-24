cmake_minimum_required(VERSION 3.0)
project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ForradiaCommon
file(GLOB_RECURSE COMMON_SOURCES "code/common/src/*.cpp")
add_library(ForradiaCommon ${COMMON_SOURCES})
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(ForradiaCommon PRIVATE ${PYTHON_LIBRARIES})
target_link_libraries(ForradiaCommon PRIVATE SDL2 SDL2_image SDL2_ttf fmt GL GLEW)
target_precompile_headers(ForradiaCommon PUBLIC code/common/src/StdAfx.hpp)

# ForradiaCore
file(GLOB_RECURSE CORE_SOURCES "code/core/src/*.cpp")
add_library(ForradiaCore ${CORE_SOURCES})
target_include_directories(ForradiaCore PRIVATE "code/common/src")
target_link_libraries(ForradiaCore ForradiaCommon assimp)
target_precompile_headers(ForradiaCore PUBLIC code/core/src/StdAfx.hpp)

# ForradiaTheme0WorldStruct
file(GLOB_RECURSE WORLD_STRUCT_SOURCES "code/theme_0_world_struct/src/*.cpp")
add_library(ForradiaTheme0WorldStruct ${WORLD_STRUCT_SOURCES})
target_include_directories(ForradiaTheme0WorldStruct PRIVATE "code/common/src")
target_link_libraries(ForradiaTheme0WorldStruct ForradiaCommon)
target_precompile_headers(ForradiaTheme0WorldStruct PUBLIC code/theme_0_world_struct/src/StdAfx.hpp)

# ForradiaTheme0WorldGen
file(GLOB_RECURSE WORLD_GEN_SOURCES "code/theme_0_world_gen/src/*.cpp")
add_library(ForradiaTheme0WorldGen ${WORLD_GEN_SOURCES})
target_include_directories(ForradiaTheme0WorldGen PRIVATE
    "code/common/src"
    "code/theme_0_world_struct/src"
    "code/theme_0_game_props/src"
)
target_link_libraries(ForradiaTheme0WorldGen ForradiaTheme0WorldStruct)
target_precompile_headers(ForradiaTheme0WorldGen PUBLIC code/theme_0_world_gen/src/StdAfx.hpp)

# ForradiaTheme0Essentials
file(GLOB_RECURSE THEME_0_ESSENTIALS_SOURCES "code/theme_0_essentials/src/*.cpp")
add_library(ForradiaTheme0Essentials ${THEME_0_ESSENTIALS_SOURCES})
target_include_directories(ForradiaTheme0Essentials PRIVATE
    "code/common/src"
    "code/core/src"
    "code/theme_0_world_struct/src"
    "code/theme_0_game_props/src"
)
target_link_libraries(ForradiaTheme0Essentials
    ForradiaCore
    ForradiaTheme0WorldStruct
)
target_precompile_headers(ForradiaTheme0Essentials PUBLIC code/theme_0_essentials/src/StdAfx.hpp)

# ForradiaTheme0
file(GLOB_RECURSE SOURCES "code/theme_0/src/*.cpp")
add_executable(Forradia ${SOURCES})
target_precompile_headers(Forradia PUBLIC code/theme_0/src/StdAfx.hpp)
target_include_directories(Forradia PRIVATE
    "code/theme_0/src"
    "code/common/src"
    "code/core/src"
    "code/theme_0_world_struct/src"
    "code/theme_0_game_props/src"
    "code/theme_0_world_gen/src"
    "code/theme_0_essentials/src"
)
target_link_libraries(Forradia PRIVATE
    ForradiaCommon
    ForradiaCore
    ForradiaTheme0WorldStruct
    ForradiaTheme0WorldGen
    ForradiaTheme0Essentials
    #GLU
)
install(TARGETS Forradia RUNTIME DESTINATION bin)
