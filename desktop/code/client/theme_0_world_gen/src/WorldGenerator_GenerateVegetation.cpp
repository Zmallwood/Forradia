//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateForests() const
    {
        // Create dense forest clusters
        auto numForests{15 + GetRandomInt(10)};

        for (auto i = 0; i < numForests; i++)
        {
            auto centerX{GetRandomInt(m_size.width)};
            auto centerY{GetRandomInt(m_size.height)};

            auto tile = m_worldArea->GetTile(centerX, centerY);
            if (!tile || !IsValidForTree(centerX, centerY))
            {
                continue;
            }

            auto radius{CInt(8 * m_scale + GetRandomInt(12 * m_scale))};
            auto treeDensity{0.1f + GetRandomInt(20) / 100.0f}; // 0.4 to 0.6

            // Decide on forest type (fir or birch dominated)
            auto useFir{GetRandomInt(100) < 60};

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    if (!m_worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    if (!IsValidForTree(x, y))
                    {
                        continue;
                    }

                    auto distance = GetDistance(x, y, centerX, centerY);
                    if (distance > radius)
                    {
                        continue;
                    }

                    // Higher density in center, lower at edges
                    auto normalizedDistance = distance / radius;
                    auto localDensity = treeDensity * (1.0f - normalizedDistance * 0.5f);

                    if (GetRandomInt(1000) < static_cast<int>(localDensity * 1000.0f))
                    {
                        auto forestTile = m_worldArea->GetTile(x, y);
                        if (forestTile)
                        {
                            forestTile->GetObjectsStack()->ClearObjects();

                            // Mix of tree types, but favor one type
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

                            // Add undergrowth in forests
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

    void WorldGenerator::GenerateMeadows() const
    {
        // Create meadow areas with flowers and tall grass
        auto numMeadows{20 + GetRandomInt(15)};

        for (auto i = 0; i < numMeadows; i++)
        {
            auto centerX{GetRandomInt(m_size.width)};
            auto centerY{GetRandomInt(m_size.height)};

            auto tile = m_worldArea->GetTile(centerX, centerY);
            if (!tile || !IsValidForTree(centerX, centerY))
            {
                continue;
            }

            // Meadows prefer grass ground
            if (tile->GetGround() != Hash("GroundGrass"))
            {
                continue;
            }

            auto radius{CInt(5 * m_scale + GetRandomInt(8 * m_scale))};
            auto flowerDensity{0.15f + GetRandomInt(15) / 100.0f}; // 0.15 to 0.3
            auto grassDensity{0.2f + GetRandomInt(20) / 100.0f};   // 0.2 to 0.4

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    if (!m_worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    if (!IsValidForTree(x, y))
                    {
                        continue;
                    }

                    auto meadowTile = m_worldArea->GetTile(x, y);
                    if (!meadowTile || meadowTile->GetGround() != Hash("GroundGrass"))
                    {
                        continue;
                    }

                    auto distance = GetDistance(x, y, centerX, centerY);
                    if (distance > radius)
                    {
                        continue;
                    }

                    // Add flowers
                    if (GetRandomInt(1000) < static_cast<int>(flowerDensity * 1000.0f))
                    {
                        meadowTile->GetObjectsStack()->ClearObjects();
                        meadowTile->GetObjectsStack()->AddObject("ObjectPinkFlower");
                    }
                    // Add tall grass (only if no flower was placed)
                    else if (GetRandomInt(1000) < static_cast<int>(grassDensity * 1000.0f))
                    {
                        // Only add if we didn't just add a flower above
                        // (This is handled by the else if, so we're good)
                        meadowTile->GetObjectsStack()->ClearObjects();
                        meadowTile->GetObjectsStack()->AddObject("ObjectTallGrass");
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateObjectsInBiomes() const
    {
        // Add scattered objects throughout the world based on biomes
        // This complements the forests and meadows

        // Scattered trees outside of forests
        auto numScatteredTrees{300 * m_scale + GetRandomInt(150 * m_scale)};

        for (auto i = 0; i < numScatteredTrees; i++)
        {
            auto x{GetRandomInt(m_size.width)};
            auto y{GetRandomInt(m_size.height)};

            auto tile = m_worldArea->GetTile(x, y);
            if (!tile || !IsValidForTree(x, y))
            {
                continue;
            }

            // Prefer grass ground for scattered trees
            if (tile->GetGround() == Hash("GroundGrass") && GetRandomInt(100) < 8)
            {
                tile->GetObjectsStack()->ClearObjects();
                if (GetRandomInt(100) < 50)
                {
                    tile->GetObjectsStack()->AddObject("ObjectFirTree");
                }
                else
                {
                    tile->GetObjectsStack()->AddObject("ObjectBirchTree");
                }
            }
        }

        // Scattered bushes
        auto numScatteredBushes{1000 * m_scale + GetRandomInt(100 * m_scale)};

        for (auto i = 0; i < numScatteredBushes; i++)
        {
            auto x{GetRandomInt(m_size.width)};
            auto y{GetRandomInt(m_size.height)};

            auto tile = m_worldArea->GetTile(x, y);
            if (!tile || !IsValidForTree(x, y))
            {
                continue;
            }

            if (GetRandomInt(100) < 8)
            {
                tile->GetObjectsStack()->ClearObjects();
                if (GetRandomInt(100) < 50)
                {
                    tile->GetObjectsStack()->AddObject("ObjectBush1");
                }
                else
                {
                    tile->GetObjectsStack()->AddObject("ObjectBush2");
                }
            }
        }

        // Stone boulders - prefer higher elevation areas
        auto numBoulders{150 * m_scale + GetRandomInt(100 * m_scale)};

        for (auto i = 0; i < numBoulders; i++)
        {
            auto x{GetRandomInt(m_size.width)};
            auto y{GetRandomInt(m_size.height)};

            auto tile = m_worldArea->GetTile(x, y);
            if (!tile || tile->GetWaterDepth() >= 4)
            {
                continue;
            }

            // Higher elevation = more likely to have boulders
            auto elevation = tile->GetElevation();
            auto boulderProbability = 3 + (elevation / 5); // 3% base, +1% per 5 elevation

            if (GetRandomInt(100) < boulderProbability)
            {
                tile->GetObjectsStack()->ClearObjects();
                tile->GetObjectsStack()->AddObject("ObjectStoneBoulder");
            }
        }
    }
}

