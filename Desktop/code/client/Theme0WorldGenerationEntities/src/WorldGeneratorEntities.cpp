//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorEntities.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

#include "Creature.hpp"

#include "Robot.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorEntities::GenerateEntities() const
    {
        GenerateCreaturesInEcosystems();

        GenerateRobotsInAreas();
    }

    void WorldGeneratorEntities::GenerateRobotsInAreas() const
    {
        auto worldArea{GetWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto worldScaling{GetWorldScaling()};

        // Generate robots in clusters and patrol areas.
        // Robots avoid water but can be found in various terrain types.

        // First, create robot patrol clusters.

        auto numRobotClusters{8 + GetRandomInt(7)};

        for (auto cluster = 0; cluster < numRobotClusters; cluster++)
        {
            auto centerX{GetRandomInt(worldAreaSize.width)};

            auto centerY{GetRandomInt(worldAreaSize.height)};

            auto centerTile = worldArea->GetTile(centerX, centerY);

            if (!centerTile || centerTile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            auto clusterRadius{10 + GetRandomInt(15)};

            auto robotsInCluster{5 + GetRandomInt(10)};

            for (auto r = 0; r < robotsInCluster; r++)
            {
                auto angle = GetRandomInt(360) * M_PI / 180.0f;

                auto distance = GetRandomInt(clusterRadius);

                auto robotX = centerX + CInt(std::cos(angle) * distance);

                auto robotY = centerY + CInt(std::sin(angle) * distance);

                if (!worldArea->IsValidCoordinate(robotX, robotY))
                {
                    continue;
                }

                auto robotTile = worldArea->GetTile(robotX, robotY);

                if (!robotTile || robotTile->GetRobot() ||
                    robotTile->GetGround() == Hash("GroundWater"))
                {
                    continue;
                }

                auto newRobot{std::make_shared<Theme0::Robot>("RobotMechWolf", robotX, robotY)};

                robotTile->SetRobot(newRobot);

                worldArea->GetRobotsMirrorRef().insert({robotTile->GetRobot(), {robotX, robotY}});
            }
        }

        // Also add scattered robots throughout the world.

        auto numScatteredRobots{120 * worldScaling + GetRandomInt(40 * worldScaling)};

        for (auto i = 0; i < numScatteredRobots; i++)
        {
            auto x{GetRandomInt(worldAreaSize.width)};

            auto y{GetRandomInt(worldAreaSize.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (!tile || tile->GetRobot() || tile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            // Robots can appear anywhere except water, with equal probability.

            if (GetRandomInt(100) < 15)
            {
                auto newRobot{std::make_shared<Theme0::Robot>("RobotMechWolf", x, y)};

                tile->SetRobot(newRobot);

                worldArea->GetRobotsMirrorRef().insert({tile->GetRobot(), {x, y}});
            }
        }
    }

    bool WorldGeneratorEntities::IsNearWater(int x, int y, int radius) const
    {
        // Check all tiles in the radius.

        for (auto checkY = y - radius; checkY <= y + radius; checkY++)
        {
            for (auto checkX = x - radius; checkX <= x + radius; checkX++)
            {
                // Skip if the tile is out of bounds.

                if (!GetWorldArea()->IsValidCoordinate(checkX, checkY))
                {
                    continue;
                }

                // Get the tile at the given coordinates.

                auto tile{GetWorldArea()->GetTile(checkX, checkY)};

                // Check if the tile is water.

                if (tile && tile->GetGround() == Hash("GroundWater"))
                {
                    // Calculate the distance between the tile and the given coordinates.

                    auto distance{GetDistance(x, y, checkX, checkY)};

                    // Return true if the distance is less than or equal to the radius.

                    if (distance <= radius)
                    {
                        return true;
                    }
                }
            }
        }

        // Return false if no adjacent tile is water.

        return false;
    }
}