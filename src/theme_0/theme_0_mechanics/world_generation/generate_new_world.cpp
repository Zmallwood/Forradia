/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "generate_new_world.hpp"
#include "sub/clear_with_dirt.hpp"
#include "sub/generate_creatures.hpp"
#include "sub/generate_elevation.hpp"
#include "sub/generate_grass.hpp"
#include "sub/generate_lakes.hpp"
#include "sub/generate_objects.hpp"
#include "sub/generate_rivers.hpp"
#include "sub/generate_rock.hpp"

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