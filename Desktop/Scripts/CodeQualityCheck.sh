#!/usr/bin/env bash
cd ..
shopt -s globstar  # Enable recursive globbing
INCLUDE_FLAGS=$(find code/client -type d -name "src" -exec printf -- "--extra-arg=-I%s " {} \;)
clang-tidy code/client/CommonCoreUtilities/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CommonGeneral/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CommonLang/**/*.hpp $INCLUDE_FLAGS -p build -- --std=c++20 # Note: Only look for headers
clang-tidy code/client/CommonMatter/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CommonUtilities/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreAssets/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreEngine/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreGraphicsDevices/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreGUI/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreInput/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreMinorComponents/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreRenderingColors2D/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreRenderingCommon/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreRenderingGround/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreRenderingImages2D/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreRenderingModels/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreRenderingSky/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreRenderingText/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/CoreScenes/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0Core/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0CustomGUI/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0Essentials/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0Properties/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0Sceness/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0WorldGenerationCommon/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build  --std=c++20--
clang-tidy code/client/Theme0WorldGenerationEntities/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0WorldGenerationGround/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0WorldGenerationMain/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0WorldGenerationObjects/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0WorldGenerationWater/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
clang-tidy code/client/Theme0WorldStructure/**/*.{cpp,hpp} $INCLUDE_FLAGS -p build -- --std=c++20
