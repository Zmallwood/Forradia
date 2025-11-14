//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorObjects.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorObjects::GenerateObjects() const
    {
        GenerateForests();

        GenerateMeadows();

        GenerateObjectsInBiomes();
    }

    void WorldGeneratorObjects::GenerateForests() const
    {
        auto worldArea{GetWorldArea()};

        auto size{worldArea->GetSize()};

        auto scale{GetScale()};

        // Create dense forest clusters.

        auto numForests{15 + GetRandomInt(10)};

        for (auto i = 0; i < numForests; i++)
        {
            auto centerX{GetRandomInt(size.width)};

            auto centerY{GetRandomInt(size.height)};

            auto tile{worldArea->GetTile(centerX, centerY)};

            if (!tile || !IsValidForTree(centerX, centerY))
            {
                continue;
            }

            auto radius{CInt(8 * scale + GetRandomInt(12 * scale))};

            auto treeDensity{0.1f + GetRandomInt(20) / 100.0f}; // 0.4 to 0.6.

            // Decide on forest type (fir or birch dominated).

            auto useFir{GetRandomInt(100) < 60};

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    if (!IsValidForTree(x, y))
                    {
                        continue;
                    }

                    auto distance{GetDistance(x, y, centerX, centerY)};

                    if (distance > radius)
                    {
                        continue;
                    }

                    // Higher density in center, lower at edges.

                    auto normalizedDistance{distance / radius};

                    auto localDensity{treeDensity * (1.0f - normalizedDistance * 0.5f)};

                    if (GetRandomInt(1000) < static_cast<int>(localDensity * 1000.0f))
                    {
                        auto forestTile{worldArea->GetTile(x, y)};

                        if (forestTile)
                        {
                            forestTile->GetObjectsStack()->ClearObjects();

                            // Mix of tree types, but favor one type.

                            if (useFir)
                            {
                                if (GetRandomInt(100) < 70)
                                {
                                    forestTile->GetObjectsStack()->AddObject("ObjectFirTree");
                                }
                                else
                                {
                                    forestTile->GetObjectsStack()->AddObject("ObjectBirchTree");
                                }
                            }
                            else
                            {
                                if (GetRandomInt(100) < 70)
                                {
                                    forestTile->GetObjectsStack()->AddObject("ObjectBirchTree");
                                }
                                else
                                {
                                    forestTile->GetObjectsStack()->AddObject("ObjectFirTree");
                                }
                            }

                            // Add undergrowth in forests.

                            if (GetRandomInt(100) < 25)
                            {
                                if (GetRandomInt(100) < 50)
                                {
                                    forestTile->GetObjectsStack()->AddObject("ObjectBush1");
                                }
                                else
                                {
                                    forestTile->GetObjectsStack()->AddObject("ObjectBush2");
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void WorldGeneratorObjects::GenerateMeadows() const
    {
        auto worldArea{GetWorldArea()};

        auto size{worldArea->GetSize()};

        auto scale{GetScale()};

        // Create meadow areas with flowers and tall grass.

        auto numMeadows{20 + GetRandomInt(15)};

        for (auto i = 0; i < numMeadows; i++)
        {
            auto centerX{GetRandomInt(size.width)};

            auto centerY{GetRandomInt(size.height)};

            auto tile{worldArea->GetTile(centerX, centerY)};

            if (!tile || !IsValidForTree(centerX, centerY))
            {
                continue;
            }

            // Meadows prefer grass ground.

            if (tile->GetGround() != Hash("GroundGrass"))
            {
                continue;
            }

            auto radius{CInt(5 * scale + GetRandomInt(8 * scale))};

            // 0.15 to 0.3.
            auto flowerDensity{0.15f + GetRandomInt(15) / 100.0f};

            // 0.2 to 0.4.
            auto grassDensity{0.2f + GetRandomInt(20) / 100.0f};

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    if (!IsValidForTree(x, y))
                    {
                        continue;
                    }

                    auto meadowTile{worldArea->GetTile(x, y)};

                    if (!meadowTile || meadowTile->GetGround() != Hash("GroundGrass"))
                    {
                        continue;
                    }

                    auto distance{GetDistance(x, y, centerX, centerY)};

                    if (distance > radius)
                    {
                        continue;
                    }

                    // Add flowers.

                    if (GetRandomInt(1000) < static_cast<int>(flowerDensity * 1000.0f))
                    {
                        meadowTile->GetObjectsStack()->ClearObjects();

                        meadowTile->GetObjectsStack()->AddObject("ObjectPinkFlower");
                    }

                    // Add tall grass (only if no flower was placed).

                    else if (GetRandomInt(1000) < static_cast<int>(grassDensity * 1000.0f))
                    {
                        // Only add if we didn't just add a flower above.
                        // (This is handled by the else if, so we're good).

                        meadowTile->GetObjectsStack()->ClearObjects();

                        meadowTile->GetObjectsStack()->AddObject("ObjectTallGrass");
                    }
                }
            }
        }
    }

    bool WorldGeneratorObjects::IsValidForTree(int x, int y) const
    {
        // Check if the coordinates are valid.

        if (!GetWorldArea()->IsValidCoordinate(x, y))
        {
            // Return false if not valid.

            return false;
        }

        // Get the tile at the given coordinates.

        auto tile = GetWorldArea()->GetTile(x, y);

        // Return false if the tile is not found.

        if (!tile)
        {
            // Return false if the tile is not found.

            return false;
        }

        // Get the ground type of the tile.

        auto ground{tile->GetGround()};

        // Trees can't grow in water or on bare rock

        return ground != Hash("GroundWater") && ground != Hash("GroundRock") &&
               tile->GetWaterDepth() == 0;
    }
}