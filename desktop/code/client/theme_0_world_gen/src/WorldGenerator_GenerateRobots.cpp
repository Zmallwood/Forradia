//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "Robot.hpp"

#include <cmath>

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateRobotsInAreas() const
    {
        // Generate robots in clusters and patrol areas
        // Robots avoid water but can be found in various terrain types

        // First, create robot patrol clusters
        auto numRobotClusters{8 + GetRandomInt(7)};

        for (auto cluster = 0; cluster < numRobotClusters; cluster++)
        {
            auto centerX{GetRandomInt(m_size.width)};
            auto centerY{GetRandomInt(m_size.height)};

            auto centerTile = m_worldArea->GetTile(centerX, centerY);
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

                if (!m_worldArea->IsValidCoordinate(robotX, robotY))
                {
                    continue;
                }

                auto robotTile = m_worldArea->GetTile(robotX, robotY);
                if (!robotTile || robotTile->GetRobot() ||
                    robotTile->GetGround() == Hash("GroundWater"))
                {
                    continue;
                }

                auto newRobot = std::make_shared<Theme0::Robot>("RobotMechWolf", robotX, robotY);

                robotTile->SetRobot(newRobot);

                m_worldArea->GetRobotsMirrorRef().insert({robotTile->GetRobot(), {robotX, robotY}});
            }
        }

        // Also add scattered robots throughout the world
        auto numScatteredRobots{120 * m_scale + GetRandomInt(40 * m_scale)};

        for (auto i = 0; i < numScatteredRobots; i++)
        {
            auto x{GetRandomInt(m_size.width)};
            auto y{GetRandomInt(m_size.height)};

            auto tile = m_worldArea->GetTile(x, y);
            if (!tile || tile->GetRobot() || tile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            // Robots can appear anywhere except water, with equal probability
            if (GetRandomInt(100) < 15)
            {
                auto newRobot = std::make_shared<Theme0::Robot>("RobotMechWolf", x, y);

                tile->SetRobot(newRobot);

                m_worldArea->GetRobotsMirrorRef().insert({tile->GetRobot(), {x, y}});
            }
        }
    }
}
