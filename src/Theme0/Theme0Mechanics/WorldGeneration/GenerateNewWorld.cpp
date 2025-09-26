#include "GenerateNewWorld.hpp"
#include "Sub/ClearWithGrass.hpp"
#include "Sub/GenerateWater.hpp"
#include "Sub/GenerateObjects.hpp"
#include "Sub/GenerateMobs.hpp"
#include "Sub/GenerateElevation.hpp"

namespace Forradia
{
    void GenerateNewWorld()
    {
        ClearWithGrass();

        GenerateWater();

        GenerateObjects();

        GenerateElevation();

        GenerateMobs();
    }
}