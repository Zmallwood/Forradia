/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateNewWorld.hpp"
#include "Sub/ClearWithDirt.hpp"
#include "Sub/GenerateGrass.hpp"
#include "Sub/GenerateWater.hpp"
#include "Sub/GenerateObjects.hpp"
#include "Sub/GenerateMobs.hpp"
#include "Sub/GenerateElevation.hpp"

namespace Forradia
{
    void GenerateNewWorld()
    {
        ClearWithDirt();

        GenerateGrass();

        GenerateWater();

        GenerateElevation();

        GenerateObjects();

        GenerateMobs();
    }
}