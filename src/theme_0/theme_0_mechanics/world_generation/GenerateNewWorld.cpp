/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateNewWorld.hpp"
#include "sub/ClearWithDirt.hpp"
#include "sub/GenerateCreatures.hpp"
#include "sub/GenerateElevation.hpp"
#include "sub/GenerateGrass.hpp"
#include "sub/GenerateLakes.hpp"
#include "sub/GenerateObjects.hpp"
#include "sub/GenerateRivers.hpp"
#include "sub/GenerateRock.hpp"

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