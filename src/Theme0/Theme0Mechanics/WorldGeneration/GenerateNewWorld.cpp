/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateNewWorld.hpp"
#include "Sub/ClearWithDirt.hpp"
#include "Sub/GenerateCreatures.hpp"
#include "Sub/GenerateElevation.hpp"
#include "Sub/GenerateGrass.hpp"
#include "Sub/GenerateLakes.hpp"
#include "Sub/GenerateObjects.hpp"
#include "Sub/GenerateRivers.hpp"
#include "Sub/GenerateRock.hpp"

namespace Forradia {
  void GenerateNewWorld() {
    ClearWithDirt();

    GenerateGrass();

    GenerateLakes();

    GenerateElevation();

    GenerateRock();

    GenerateRivers();

    GenerateObjects();

    GenerateCreatures();
  }
}