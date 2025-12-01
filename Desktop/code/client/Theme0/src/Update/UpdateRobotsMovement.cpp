//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "UpdateRobotsMovement.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Robot.hpp"
#include "NumbersUtilities.hpp"

namespace AAK
{
    namespace Forradia::Theme0::GameplayCore
    {
        void UpdateRobotsMovement()
        {
            auto worldArea{_<World>().GetCurrentWorldArea()};

            auto &robots{worldArea->GetRobotsMirrorRef()};

            auto now{GetTicks()};

            for (auto it = robots.begin(); it != robots.end();)
            {
                auto robot{it->first};

                auto position{it->second};

                if (now < robot->GetTicksLastMovement() + InvertSpeed(robot->GetMovementSpeed()))
                {
                    ++it;

                    continue;
                }

                auto origin{robot->GetOrigin()};

                auto destination{robot->GetDestination()};

                if (destination.x == -1 && destination.y == -1)
                {
                    auto newDestination{origin.x + GetRandomInt(9) - 4};

                    auto newDestinationY{origin.y + GetRandomInt(9) - 4};

                    robot->SetDestination({newDestination, newDestinationY});
                }

                auto worldArea{_<World>().GetCurrentWorldArea()};

                auto &robots{worldArea->GetRobotsMirrorRef()};

                auto dX{robot->GetDestination().x - position.x};

                auto dY{robot->GetDestination().y - position.y};

                auto normalizedDX{Normalize(dX)};

                auto normalizedDY{Normalize(dY)};

                auto newX{position.x + normalizedDX};

                auto newY{position.y + normalizedDY};

                Point newPosition{newX, newY};

                if (newPosition == robot->GetDestination())
                {
                    robot->SetDestination({-1, -1});
                }

                auto tile{worldArea->GetTile(newPosition.x, newPosition.y)};

                if (tile && !tile->GetRobot() && tile->GetGround() != Hash("GroundWater"))
                {
                    auto oldPosition{robots.at(robot)};

                    robot->SetTicksLastMovement(now);

                    auto oldTile{worldArea->GetTile(oldPosition.x, oldPosition.y)};

                    auto newTile{worldArea->GetTile(newPosition.x, newPosition.y)};

                    oldTile->SetRobot(nullptr);

                    newTile->SetRobot(robot);

                    robots.erase(robot);

                    robots.insert({robot, {newPosition.x, newPosition.y}});
                }
                else
                {
                    robot->SetDestination({-1, -1});
                }

                ++it;
            }
        }
    }
}