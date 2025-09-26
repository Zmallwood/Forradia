#include "ClearWithGrass.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"

namespace Forradia
{
    void ClearWithGrass()
    {
        auto worldArea { _<World>().GetCurrentWorldArea() };

        auto size { worldArea->GetSize() };

        for (auto y = 0; y < size.height; y++)
        {
            for (auto x = 0; x < size.width; x++)
            {
                auto tile { worldArea->GetTile(x, y) };

                if (tile)
                {
                    tile->SetGround("GroundGrass");
                }
            }
        }
    }
}