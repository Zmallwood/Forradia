cmake_minimum_required(VERSION 3.0)
project(Forradia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ForradiaCommonMatter
file(GLOB_RECURSE COMMON_MATTER_SOURCES "code/client/common_matter/src/*.cpp")
add_library(ForradiaCommonMatter ${COMMON_MATTER_SOURCES})
target_include_directories(ForradiaCommonMatter PUBLIC
    "code/client/common_matter/src"
    "code/client/common_lang/src"
)
target_precompile_headers(ForradiaCommonMatter PUBLIC code/client/common_matter/src/StdAfx.hpp)

# ForradiaCommon
file(GLOB_RECURSE COMMON_SOURCES "code/client/common_general/src/*.cpp")
add_library(ForradiaCommonGeneral ${COMMON_SOURCES})
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_include_directories(ForradiaCommonGeneral PUBLIC
    "code/client/common_lang/src"
    "code/client/common_matter/src"
    "code/client/common_general/src"
)
target_link_libraries(ForradiaCommonGeneral PRIVATE ${PYTHON_LIBRARIES})
target_link_libraries(ForradiaCommonGeneral PRIVATE ForradiaCommonMatter SDL2 SDL2_image SDL2_ttf fmt GL GLEW)
target_precompile_headers(ForradiaCommonGeneral PUBLIC code/client/common_general/src/StdAfx.hpp)

# ForradiaCommonUtilities
file(GLOB_RECURSE COMMON_UTILITIES_SOURCES "code/client/common_utilities/src/*.cpp")
add_library(ForradiaCommonUtilities ${COMMON_UTILITIES_SOURCES})
target_include_directories(ForradiaCommonUtilities PUBLIC
    "code/client/common_utilities/src"
    "code/client/common_lang/src"
)
target_precompile_headers(ForradiaCommonUtilities PUBLIC code/client/common_utilities/src/StdAfx.hpp)

# ForradiaCommonCoreUtilities
file(GLOB_RECURSE COMMON_CORE_UTILITIES_SOURCES "code/client/common_core_utilities/src/*.cpp")
add_library(ForradiaCommonCoreUtilities ${COMMON_CORE_UTILITIES_SOURCES})
target_include_directories(ForradiaCommonCoreUtilities PUBLIC
    "code/client/common_core_utilities/src"
    "code/client/common_lang/src"
    "code/client/common_matter/src"
)
target_precompile_headers(ForradiaCommonCoreUtilities PUBLIC code/client/common_core_utilities/src/StdAfx.hpp)

# ForradiaCoreGraphicsDevices
file(GLOB_RECURSE CORE_GRAPHICS_DEVICES_SOURCES "code/client/core_graphics_devices/src/*.cpp")
add_library(ForradiaCoreGrahicsDevices ${CORE_GRAPHICS_DEVICES_SOURCES})
target_include_directories(ForradiaCoreGrahicsDevices PUBLIC
    "code/client/core_graphics_devices/src"
    "code/client/common_utilities/src"
)
target_link_libraries(ForradiaCoreGrahicsDevices ForradiaCommonGeneral assimp)
target_precompile_headers(ForradiaCoreGrahicsDevices PUBLIC code/client/core_graphics_devices/src/StdAfx.hpp)

# ForradiaCoreAssets
file(GLOB_RECURSE CORE_ASSETS_SOURCES "code/client/core_assets/src/*.cpp")
add_library(ForradiaCoreAssets ${CORE_ASSETS_SOURCES})
target_include_directories(ForradiaCoreAssets PUBLIC
    "code/client/core_assets/src"
    "code/client/common_matter/src"
    "code/client/common_core_utilities/src"
    "code/client/common_general/src"
)
target_link_libraries(ForradiaCoreAssets
    ForradiaCommonUtilities
)
target_precompile_headers(ForradiaCoreAssets PUBLIC code/client/core_assets/src/StdAfx.hpp)

# ForradiaCoreInput
file(GLOB_RECURSE CORE_INPUT_SOURCES "code/client/core_input/src/*.cpp")
add_library(ForradiaCoreInput ${CORE_INPUT_SOURCES})
target_include_directories(ForradiaCoreInput PUBLIC
    "code/client/core_input/src"
)
target_precompile_headers(ForradiaCoreInput PUBLIC code/client/core_input/src/StdAfx.hpp)

# ForradiaCore
file(GLOB_RECURSE CORE_SOURCES "code/client/core/src/*.cpp")
add_library(ForradiaCore ${CORE_SOURCES})
target_include_directories(ForradiaCore PUBLIC
    "code/client/core/src"
    "code/client/theme_0_properties/src"
    "code/client/common_core_utilities/src"
    "code/client/core_assets/src"
)
target_link_libraries(ForradiaCore
    ForradiaCommonGeneral
    ForradiaCoreGrahicsDevices
    assimp
)
target_precompile_headers(ForradiaCore PUBLIC code/client/core/src/StdAfx.hpp)

# ForradiaCoreGUI
file(GLOB_RECURSE CORE_GUI_SOURCES "code/client/core_gui/src/*.cpp")
add_library(ForradiaCoreGUI ${CORE_GUI_SOURCES})
target_include_directories(ForradiaCoreGUI PUBLIC
    "code/client/core_gui/src"
    "code/client/core_graphics_devices/src"
    "code/client/core/src"
    "code/client/common_lang/src"
    "code/client/common_matter/src"
    "code/client/common_general/src"
    "code/client/common_core_utilities/src"
    "code/client/core_minor_components/src"
)
target_precompile_headers(ForradiaCoreGUI PUBLIC code/client/core_gui/src/StdAfx.hpp)
target_link_libraries(ForradiaCoreGUI
    ForradiaCoreInput
)

# ForradiaCoreScenes
file(GLOB_RECURSE CORE_SCENES_SOURCES "code/client/core_scenes/src/*.cpp")
add_library(ForradiaCoreScenes ${CORE_SCENES_SOURCES})
target_include_directories(ForradiaCoreScenes PUBLIC
    "code/client/core_scenes/src"
    "code/client/core_gui/src"
    "code/client/common_lang/src"
    "code/client/common_matter/src"
    "code/client/common_core_utilities/src"
)
target_precompile_headers(ForradiaCoreScenes PUBLIC code/client/core_scenes/src/StdAfx.hpp)

# ForradiaCoreEngine
file(GLOB_RECURSE CORE_ENGINE_SOURCES "code/client/core_engine/src/*.cpp")
add_library(ForradiaCoreEngine ${CORE_ENGINE_SOURCES})
target_include_directories(ForradiaCoreEngine PUBLIC
    "code/client/core_engine/src"
    "code/client/core_graphics_devices/src"
    "code/client/core/src"
    "code/client/core_scenes/src"
    "code/client/core_input/src"
    "code/client/common_lang/src"
    "code/client/common_matter/src"
    "code/client/common_utilities/src"
    "code/client/common_general/src"
    "code/client/core_minor_components/src"
)
target_precompile_headers(ForradiaCoreEngine PUBLIC code/client/core_engine/src/StdAfx.hpp)

# ForradiaTheme0WorldStruct
file(GLOB_RECURSE WORLD_STRUCT_SOURCES "code/client/theme_0_world_struct/src/*.cpp")
add_library(ForradiaTheme0WorldStruct ${WORLD_STRUCT_SOURCES})
target_include_directories(ForradiaTheme0WorldStruct PUBLIC
    "code/client/theme_0_world_struct/src"
    "code/client/common_utilities/src"
    "code/client/common_core_utilities/src"
)
target_link_libraries(ForradiaTheme0WorldStruct ForradiaCommonGeneral)
target_precompile_headers(ForradiaTheme0WorldStruct PUBLIC code/client/theme_0_world_struct/src/StdAfx.hpp)

# ForradiaTheme0Properties
file(GLOB_RECURSE THEME_0_PROPERTIES "code/client/theme_0_properties/src/*.cpp")
add_library(ForradiaTheme0Properties ${THEME_0_PROPERTIES})
target_include_directories(ForradiaTheme0Properties PUBLIC
    "code/client/theme_0_properties/src"
    "code/client/common_lang/src"
    "code/client/common_matter/src"
)
target_precompile_headers(ForradiaTheme0Properties PUBLIC code/client/theme_0_properties/src/StdAfx.hpp)

# ForradiaTheme0WorldGen
file(GLOB_RECURSE WORLD_GEN_SOURCES "code/client/theme_0_world_gen/src/*.cpp")
add_library(ForradiaTheme0WorldGen ${WORLD_GEN_SOURCES})
target_include_directories(ForradiaTheme0WorldGen PUBLIC
    "code/client/theme_0_world_gen/src"
    "code/client/theme_0_properties/src"
)
target_link_libraries(ForradiaTheme0WorldGen ForradiaTheme0WorldStruct)
target_precompile_headers(ForradiaTheme0WorldGen PUBLIC code/client/theme_0_world_gen/src/StdAfx.hpp)

# ForradiaTheme0Essentials
file(GLOB_RECURSE THEME_0_ESSENTIALS_SOURCES "code/client/theme_0_essentials/src/*.cpp")
add_library(ForradiaTheme0Essentials ${THEME_0_ESSENTIALS_SOURCES})
target_include_directories(ForradiaTheme0Essentials PUBLIC
    "code/client/common_lang/src"
    "code/client/theme_0_world_struct/src"
)
target_link_libraries(ForradiaTheme0Essentials
    ForradiaCore
    ForradiaTheme0WorldStruct
)
target_precompile_headers(ForradiaTheme0Essentials PUBLIC code/client/theme_0_essentials/src/StdAfx.hpp)

# ForradiaCoreMinorComponents
file(GLOB_RECURSE CORE_MINOR_COMPONENTS_SOURCES "code/client/core_minor_components/src/*.cpp")
add_library(ForradiaCoreMinorComponents ${CORE_MINOR_COMPONENTS_SOURCES})
target_include_directories(ForradiaCoreMinorComponents PUBLIC
    "code/client/core_minor_components/src"
    "code/client/core_graphics_devices/src"
    "code/client/core/src"
    "code/client/common_lang/src"
    "code/client/common_matter/src"
    "code/client/common_general/src"
    "code/client/common_core_utilities/src"
)
target_precompile_headers(ForradiaCoreMinorComponents PUBLIC code/client/core_minor_components/src/StdAfx.hpp)

# ForradiaTheme0
file(GLOB_RECURSE SOURCES "code/client/theme_0/src/*.cpp")
add_executable(Forradia ${SOURCES})
target_precompile_headers(Forradia PUBLIC code/client/theme_0/src/StdAfx.hpp)
target_include_directories(Forradia PUBLIC
    "code/client/theme_0/src"
    "code/client/theme_0_essentials/src"
)
target_link_libraries(Forradia PRIVATE
    ForradiaCommonGeneral
    ForradiaCore
    ForradiaTheme0WorldStruct
    ForradiaTheme0WorldGen
    ForradiaTheme0Essentials
    ForradiaCommonUtilities
    ForradiaCommonCoreUtilities
    ForradiaCoreAssets
    ForradiaCoreGUI
    ForradiaCoreScenes
    ForradiaCoreEngine
    ForradiaTheme0Properties
    ForradiaCoreMinorComponents
)
install(TARGETS Forradia RUNTIME DESTINATION bin)
