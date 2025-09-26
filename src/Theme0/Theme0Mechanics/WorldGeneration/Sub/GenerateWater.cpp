#include "GenerateWater.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"

namespace Forradia
{
    void GenerateWater()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        auto numLakes{20 + RandomInt(5)};

        for (auto i = 0; i < numLakes; i++)
        {
            auto xCenter{RandomInt(size.width)};
            auto yCenter{RandomInt(size.height)};
            auto radius{3 + RandomInt(5)};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    auto dx{x - xCenter};
                    auto dy{y - yCenter};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{worldArea->GetTile(x, y)};

                        if (tile)
                        {
                            tile->SetGround("GroundWater");
                        }
                    }
                }
            }
        }
    }
}