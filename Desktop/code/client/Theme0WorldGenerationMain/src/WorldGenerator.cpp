/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "WorldGenerator.hpp"
#include "WorldGeneratorEntities.hpp"
#include "WorldGeneratorGround.hpp"
#include "WorldGeneratorObjects.hpp"
#include "WorldGeneratorWater.hpp"

namespace Forradia::Theme0 {
auto WorldGenerator::GenerateNewWorld() const -> void {
  this->Prepare();

  _<WorldGeneratorGround>().GenerateGroundWithElevation();
  _<WorldGeneratorWater>().GenerateWater();
  _<WorldGeneratorObjects>().GenerateObjects();
  _<WorldGeneratorEntities>().GenerateEntities();
}

auto WorldGenerator::Prepare() const -> void {
  _<WorldGeneratorGround>().Prepare();
  _<WorldGeneratorWater>().Prepare();
  _<WorldGeneratorObjects>().Prepare();
  _<WorldGeneratorEntities>().Prepare();
}
}
