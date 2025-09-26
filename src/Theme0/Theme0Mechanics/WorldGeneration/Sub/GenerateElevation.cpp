#include "GenerateElevation.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"

namespace Forradia
{
    void GenerateElevation()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        auto numHills{40 + RandomInt(5)};

        for (auto i = 0; i < numHills; i++)
        {
            auto xCenter{RandomInt(size.width)};
            auto yCenter{RandomInt(size.height)};
            auto maxRadius{5 + RandomInt(5)};

            for (auto r = maxRadius; r >= 0; r--)
            {
                for (auto y = yCenter - r; y <= yCenter + r; y++)
                {
                    for (auto x = xCenter - r; x <= xCenter + r; x++)
                    {
                        if (!worldArea->IsValidCoordinate(x, y))
                        {
                            continue;
                        }

                        auto dx{x - xCenter};
                        auto dy{y - yCenter};

                        if (dx * dx + dy * dy <= r * r)
                        {
                            auto tile{worldArea->GetTile(x, y)};

                            if (tile && tile->GetGround() != Hash("GroundWater"))
                            {
                                auto tileN{worldArea->GetTile(x, y - 1)};
                                auto tileS{worldArea->GetTile(x, y + 1)};
                                auto tileW{worldArea->GetTile(x - 1, y)};
                                auto tileE{worldArea->GetTile(x + 1, y)};
                                auto tileNW{worldArea->GetTile(x - 1, y - 1)};
                                auto tileNE{worldArea->GetTile(x + 1, y - 1)};
                                auto tileSW{worldArea->GetTile(x - 1, y + 1)};
                                auto tileSE{worldArea->GetTile(x + 1, y + 1)};

                                if (tileN && tileN->GetElevation() < tile->GetElevation())
                                {
                                    continue;
                                }

                                if (tileS && tileS->GetElevation() < tile->GetElevation())
                                {
                                    continue;
                                }

                                if (tileW && tileW->GetElevation() < tile->GetElevation())
                                {
                                    continue;
                                }

                                if (tileE && tileE->GetElevation() < tile->GetElevation())
                                {
                                    continue;
                                }

                                if (tileNW && tileNW->GetElevation() < tile->GetElevation())
                                {
                                    continue;
                                }

                                if (tileNE && tileNE->GetElevation() < tile->GetElevation())
                                {
                                    continue;
                                }

                                if (tileSW && tileSW->GetElevation() < tile->GetElevation())
                                {
                                    continue;
                                }

                                if (tileSE && tileSE->GetElevation() < tile->GetElevation())
                                {
                                    continue;
                                }

                                tile->SetElevation(tile->GetElevation() + 1);
                            }
                        }
                    }
                }
            }
        }
    }
}