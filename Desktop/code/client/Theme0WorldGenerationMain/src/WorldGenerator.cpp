//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "WorldGenerator.hpp"
#include "WorldGeneratorEntities.hpp"
#include "WorldGeneratorGround.hpp"
#include "WorldGeneratorObjects.hpp"
#include "WorldGeneratorWater.hpp"

namespace Forradia::Theme0 {
void WorldGenerator::GenerateNewWorld() const {
  this->Prepare();

  _<WorldGeneratorGround>().GenerateGroundWithElevation();
  _<WorldGeneratorWater>().GenerateWater();
  _<WorldGeneratorObjects>().GenerateObjects();
  _<WorldGeneratorEntities>().GenerateEntities();
}

void WorldGenerator::Prepare() const {
  _<WorldGeneratorGround>().Prepare();
  _<WorldGeneratorWater>().Prepare();
  _<WorldGeneratorObjects>().Prepare();
  _<WorldGeneratorEntities>().Prepare();
}
}