#!/usr/bin/env bash
cd ..
shopt -s globstar  # Enable recursive globbing
clang-tidy code/client/CommonCoreUtilities/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CommonGeneral/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CommonLang/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CommonMatter/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CommonUtilities/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreAssets/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreEngine/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreGraphicsDevices/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreGUI/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreInput/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreMinorComponents/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreRenderingColors2D/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreRenderingCommon/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreRenderingGround/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreRenderingImages2D/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreRenderingModels/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreRenderingSky/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreRenderingText/**/*.{cpp,hpp} -p build --
clang-tidy code/client/CoreScenes/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0Core/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0CustomGUI/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0Essentials/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0Properties/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0Sceness/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0WorldGenerationCommon/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0WorldGenerationEntities/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0WorldGenerationGround/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0WorldGenerationMain/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0WorldGenerationObjects/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0WorldGenerationWater/**/*.{cpp,hpp} -p build --
clang-tidy code/client/Theme0WorldStructure/**/*.{cpp,hpp} -p build --
