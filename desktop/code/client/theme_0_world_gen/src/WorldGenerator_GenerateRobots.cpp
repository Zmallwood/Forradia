//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "Robot.hpp"

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateRobots() const
    {
        auto numRobots{200 * m_scale +
                       GetRandomInt(15 * m_scale)};

        for (auto i = 0; i < numRobots; i++)
        {
            auto x{GetRandomInt(m_size.width)};

            auto y{GetRandomInt(m_size.height)};

            auto tile{m_worldArea->GetTile(x, y)};

            if (tile && !tile->GetRobot() &&
                tile->GetGround() != Hash("GroundWater"))
            {
                auto newRobot =
                    std::make_shared<Theme0::Robot>(
                        "RobotMechWolf", x, y);

                tile->SetRobot(newRobot);

                m_worldArea->GetRobotsMirrorRef().insert(
                    {tile->GetRobot(), {x, y}});
            }
        }
    }
}