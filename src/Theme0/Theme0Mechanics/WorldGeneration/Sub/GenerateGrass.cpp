#include "GenerateGrass.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"

namespace Forradia
{
    void GenerateGrass()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto numGrassAreas {50 + RandomInt(20)};

        for (auto i = 0; i < numGrassAreas; i++)
        {
            auto xCenter{RandomInt(worldArea->GetSize().width)};
            auto yCenter{RandomInt(worldArea->GetSize().height)};
            auto radius{4 + RandomInt(15)};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto dx{x - xCenter};
                    auto dy{y - yCenter};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{worldArea->GetTile(x, y)};

                        tile->SetGround("GroundGrass");
                    }
                }
            }
        }
    }
}