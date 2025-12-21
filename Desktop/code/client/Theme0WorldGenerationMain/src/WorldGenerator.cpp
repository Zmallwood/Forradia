/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGenerator.hpp"
#include "WorldGeneratorEntities.hpp"
#include "WorldGeneratorGround.hpp"
#include "WorldGeneratorObjects.hpp"
#include "WorldGeneratorWater.hpp"

namespace Forradia::Theme0 {
    auto WorldGenerator::GenerateNewWorld() const -> void {
        this->Prepare();

        Singleton<WorldGeneratorGround>().GenerateGroundWithElevation();
        Singleton<WorldGeneratorWater>().GenerateWater();
        Singleton<WorldGeneratorObjects>().GenerateObjects();
        Singleton<WorldGeneratorEntities>().GenerateEntities();
    }

    auto WorldGenerator::Prepare() const -> void {
        Singleton<WorldGeneratorGround>().Prepare();
        Singleton<WorldGeneratorWater>().Prepare();
        Singleton<WorldGeneratorObjects>().Prepare();
        Singleton<WorldGeneratorEntities>().Prepare();
    }
}
