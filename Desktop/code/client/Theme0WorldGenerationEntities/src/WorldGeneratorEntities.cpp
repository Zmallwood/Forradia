//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorEntities.hpp"
#include "Creature.hpp"
#include "ObjectsStack.hpp"
#include "Robot.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorEntities::GenerateEntities() const
    {
        // Do the steps to generate entities.

        GenerateCreaturesInEcosystems();

        GenerateRobotsInAreas();
    }

    void WorldGeneratorEntities::GenerateRobotsInAreas() const
    {
        // Obtain required data.

        auto worldArea{GetWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto worldScaling{GetWorldScaling()};

        // Generate robots in clusters and patrol areas.
        // Robots avoid water but can be found in various terrain types.

        // Number of robot clusters to generate.

        auto numRobotClusters{38 + GetRandomInt(7)};

        // Generate robots in clusters.

        for (auto cluster = 0; cluster < numRobotClusters; cluster++)
        {
            // Generate a random center point for the cluster.

            auto centerX{GetRandomInt(worldAreaSize.width)};

            auto centerY{GetRandomInt(worldAreaSize.height)};

            // Get the tile at the center point.

            auto centerTile = worldArea->GetTile(centerX, centerY);

            // If the tile is invalid or is water.

            if (!centerTile || centerTile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            // Generate a random radius for the cluster.

            auto clusterRadius{10 + GetRandomInt(15)};

            // Number of robots to generate in the cluster.

            auto robotsInCluster{5 + GetRandomInt(10)};

            // Generate robots in the cluster.

            for (auto r = 0; r < robotsInCluster; r++)
            {
                // Generate a random angle.

                auto angle = GetRandomInt(360) * M_PI / 180.0f;

                // Generate a random distance.

                auto distance = GetRandomInt(clusterRadius);

                // Calculate the coordinates of the robot.

                auto robotX = centerX + CInt(std::cos(angle) * distance);

                auto robotY = centerY + CInt(std::sin(angle) * distance);

                // If the coordinates are out of bounds.

                if (!worldArea->IsValidCoordinate(robotX, robotY))
                {
                    // Skip this robot.

                    continue;
                }

                // Get the tile at the coordinates.

                auto robotTile = worldArea->GetTile(robotX, robotY);

                // If the tile is invalid, or already has a robot or is water.

                if (!robotTile || robotTile->GetRobot() ||
                    robotTile->GetGround() == Hash("GroundWater"))
                {
                    // Skip this robot.

                    continue;
                }

                // Create a new robot.

                auto newRobot{std::make_shared<Theme0::Robot>("RobotMechWolf", robotX, robotY)};

                // Set the robot on the tile.

                robotTile->SetRobot(newRobot);

                // Add the robot to the world area robots mirror.

                worldArea->GetRobotsMirrorRef().insert({robotTile->GetRobot(), {robotX, robotY}});
            }
        }

        // Also add scattered robots throughout the world.

        // Number of scattered robots to generate.

        auto numScatteredRobots{220 * worldScaling + GetRandomInt(40 * worldScaling)};

        // Generate scattered robots.

        for (auto i = 0; i < numScatteredRobots; i++)
        {
            // Generate random coordinates.

            auto x{GetRandomInt(worldAreaSize.width)};

            auto y{GetRandomInt(worldAreaSize.height)};

            // Get the tile at the coordinates.

            auto tile{worldArea->GetTile(x, y)};

            // If the tile is invalid, or already has a robot or is water.

            if (!tile || tile->GetRobot() || tile->GetGround() == Hash("GroundWater"))
            {
                // Skip this robot.

                continue;
            }

            // Robots can appear anywhere except water, with equal probability.

            // If a random number is less than 15.

            if (GetRandomInt(100) < 15)
            {
                // Create a new robot.

                auto newRobot{std::make_shared<Theme0::Robot>("RobotMechWolf", x, y)};

                // Set the robot on the tile.

                tile->SetRobot(newRobot);

                // Add the robot to the world area robots mirror.

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
                // If the coordinates are out of bounds.

                if (!GetWorldArea()->IsValidCoordinate(checkX, checkY))
                {
                    // Skip this tile.

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