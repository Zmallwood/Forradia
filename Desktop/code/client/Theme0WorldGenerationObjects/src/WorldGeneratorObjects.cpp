//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorObjects.hpp"
#include "ObjectsStack.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorObjects::GenerateObjects() const
    {
        // Do the steps to generate objects in the world.

        GenerateForests();

        GenerateMeadows();

        GenerateObjectsInBiomes();
    }

    void WorldGeneratorObjects::GenerateForests() const
    {
        // Obtain required data.

        auto worldArea{GetWorldArea()};

        auto size{worldArea->GetSize()};

        auto worldScaling{GetWorldScaling()};

        // Create dense forest clusters.

        // Number of forests.

        auto numForests{15 + GetRandomInt(10)};

        // Create the forests.

        for (auto i = 0; i < numForests; i++)
        {
            // Obtain a random position for the forest.

            auto centerX{GetRandomInt(size.width)};

            auto centerY{GetRandomInt(size.height)};

            // Obtain the tile at the random position.

            auto tile{worldArea->GetTile(centerX, centerY)};

            // If the tile is invalid or not valid for a forest.

            if (!tile || !IsValidForFlora(centerX, centerY))
            {
                // Continue to the next forest.

                continue;
            }

            // Calculate the radius of the forest.

            auto radius{CInt(8 * worldScaling + GetRandomInt(12 * worldScaling))};

            // Calculate the tree density.

            auto treeDensity{0.1f + GetRandomInt(20) / 100.0f};

            // Decide on forest type (fir or birch dominated).

            auto useFir{GetRandomInt(100) < 60};

            // Create the forest.

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    // If the coordinates are invalid.

                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        // Continue to the next tile.

                        continue;
                    }

                    // If the tile is not valid for flora.

                    if (!IsValidForFlora(x, y))
                    {
                        // Continue to the next tile.

                        continue;
                    }

                    // Calculate the distance between the tile and the center of the forest.

                    auto distance{GetDistance(x, y, centerX, centerY)};

                    // If the distance is greater than the radius.

                    if (distance > radius)
                    {
                        // Continue to the next tile.

                        continue;
                    }

                    // Calculate the normalized distance.

                    auto normalizedDistance{distance / radius};

                    // Calculate the local density. Higher density in center, lower at edges.

                    auto localDensity{treeDensity * (1.0f - normalizedDistance * 0.5f)};

                    // Check if a random number is less than the local density.

                    if (GetRandomInt(1000) < static_cast<int>(localDensity * 1000.0f))
                    {
                        // Obtain the tile at the coordinates.

                        auto forestTile{worldArea->GetTile(x, y)};

                        // If the tile is valid.

                        if (forestTile)
                        {
                            // Make it so that the tile has no other objects on it.

                            forestTile->GetObjectsStack()->ClearObjects();

                            // Check if the forest should use fir or birch trees.

                            if (useFir)
                            {
                                // Add a tree of fir type with a 70% chance, otherwise add a
                                // tree of birch type.

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
                                // Add a tree of birch type with a 70% chance, otherwise add a
                                // tree of fir type.

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

                            // If a random number between 0 and 100 is less than 25.

                            if (GetRandomInt(100) < 25)
                            {
                                // Check if a random number between 0 and 100 is less than 50.

                                if (GetRandomInt(100) < 50)
                                {
                                    // Add a bush of type 1.

                                    forestTile->GetObjectsStack()->AddObject("ObjectBush1");
                                }
                                else
                                {
                                    // Otherwise add a bush of type 2.

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
        // Obtain required data.

        auto worldArea{GetWorldArea()};

        auto size{worldArea->GetSize()};

        auto worldScaling{GetWorldScaling()};

        // Create meadow areas with flowers and tall grass.

        // Number of meadows.

        auto numMeadows{20 + GetRandomInt(15)};

        // Create the meadows.

        for (auto i = 0; i < numMeadows; i++)
        {
            // Obtain a random position for the meadow.

            auto centerX{GetRandomInt(size.width)};

            auto centerY{GetRandomInt(size.height)};

            // Obtain the tile at the random position.

            auto tile{worldArea->GetTile(centerX, centerY)};

            // If the tile is invalid or not valid for a meadow.

            if (!tile || !IsValidForFlora(centerX, centerY))
            {
                // Continue to the next meadow.

                continue;
            }

            // Meadows prefer grass ground.

            if (tile->GetGround() != Hash("GroundGrass"))
            {
                continue;
            }

            // Calculate the radius of the meadow.

            auto radius{CInt(5 * worldScaling + GetRandomInt(8 * worldScaling))};

            // 0.15 to 0.3.

            auto flowerDensity{0.15f + GetRandomInt(15) / 100.0f};

            // 0.2 to 0.4.

            auto grassDensity{0.2f + GetRandomInt(20) / 100.0f};

            // Create the meadow.

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    // If the coordinates are invalid.

                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        // Continue to the next tile.

                        continue;
                    }

                    // If the tile is not valid for flora.

                    if (!IsValidForFlora(x, y))
                    {
                        // Continue to the next tile.

                        continue;
                    }

                    // Obtain the tile at the coordinates.

                    auto meadowTile{worldArea->GetTile(x, y)};

                    // If the tile is invalid or not valid for a meadow.

                    if (!meadowTile || meadowTile->GetGround() != Hash("GroundGrass"))
                    {
                        // Continue to the next tile.

                        continue;
                    }

                    // Calculate the distance between the tile and the center of the meadow.

                    auto distance{GetDistance(x, y, centerX, centerY)};

                    // If the distance is greater than the radius.

                    if (distance > radius)
                    {
                        // Continue to the next tile.

                        continue;
                    }

                    // Add flowers.

                    if (GetRandomInt(1000) < static_cast<int>(flowerDensity * 1000.0f))
                    {
                        // Clear the objects on the tile.

                        meadowTile->GetObjectsStack()->ClearObjects();

                        // Add a pink flower to the tile.

                        meadowTile->GetObjectsStack()->AddObject("ObjectPinkFlower");
                    }
                    else if (GetRandomInt(1000) < static_cast<int>(grassDensity * 1000.0f))
                    {
                        // Only add if we didn't just add a flower above.
                        // (This is handled by the else if, so we're good).

                        // Clear the objects on the tile.

                        meadowTile->GetObjectsStack()->ClearObjects();

                        // Add a tall grass to the tile.

                        meadowTile->GetObjectsStack()->AddObject("ObjectTallGrass");
                    }
                }
            }
        }
    }

    bool WorldGeneratorObjects::IsValidForFlora(int x, int y) const
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