//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

namespace Forradia
{
    namespace Theme0
    {
        void WorldGenerator::GenerateObjects() const
        {
            auto numFirTrees{2000 * m_scale +
                             GetRandomInt(50)};

            for (auto i = 0; i < numFirTrees; i++)
            {
                auto x{GetRandomInt(m_size.width)};

                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile &&
                    tile->GetGround() !=
                        Hash("ground_water") &&
                    tile->GetGround() !=
                        Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();

                    tile->GetObjectsStack()->AddTreeObject(
                        "object_fir_tree");
                }
            }

            auto numBirchTrees{2000 * m_scale +
                               GetRandomInt(50)};

            for (auto i = 0; i < numBirchTrees; i++)
            {
                auto x{GetRandomInt(m_size.width)};

                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile &&
                    tile->GetGround() !=
                        Hash("ground_water") &&
                    tile->GetGround() !=
                        Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();

                    tile->GetObjectsStack()->AddTreeObject(
                        "object_birch_tree");
                }
            }

            auto numBush1s{400 * m_scale +
                           GetRandomInt(100)};

            for (auto i = 0; i < numBush1s; i++)
            {
                auto x{GetRandomInt(m_size.width)};

                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile &&
                    tile->GetGround() !=
                        Hash("ground_water") &&
                    tile->GetGround() !=
                        Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();

                    tile->GetObjectsStack()->AddObject(
                        "object_bush1");
                }
            }

            auto numBush2s{400 * m_scale +
                           GetRandomInt(100)};

            for (auto i = 0; i < numBush2s; i++)
            {
                auto x{GetRandomInt(m_size.width)};

                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile &&
                    tile->GetGround() !=
                        Hash("ground_water") &&
                    tile->GetGround() !=
                        Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();

                    tile->GetObjectsStack()->AddObject(
                        "object_bush2");
                }
            }

            auto numPinkFlowers{400 * m_scale +
                                GetRandomInt(100)};

            for (auto i = 0; i < numPinkFlowers; i++)
            {
                auto x{GetRandomInt(m_size.width)};

                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile &&
                    tile->GetGround() !=
                        Hash("ground_water") &&
                    tile->GetGround() !=
                        Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();

                    tile->GetObjectsStack()->AddObject(
                        "object_pink_flower");
                }
            }

            auto numTallGrasses{400 * m_scale +
                                GetRandomInt(100)};

            for (auto i = 0; i < numTallGrasses; i++)
            {
                auto x{GetRandomInt(m_size.width)};

                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile &&
                    tile->GetGround() !=
                        Hash("ground_water") &&
                    tile->GetGround() !=
                        Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();

                    tile->GetObjectsStack()->AddObject(
                        "object_tall_grass");
                }
            }

            auto numStoneBoulders{200 * m_scale +
                                  GetRandomInt(100)};

            for (auto i = 0; i < numStoneBoulders; i++)
            {
                auto x{GetRandomInt(m_size.width)};

                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && tile->GetWaterDepth() < 4)
                {
                    tile->GetObjectsStack()->ClearObjects();

                    tile->GetObjectsStack()->AddObject(
                        "object_stone_boulder");
                }
            }
        }
    }
}