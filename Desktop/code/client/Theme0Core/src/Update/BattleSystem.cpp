//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "BattleSystem.hpp"

#include "GUIChatBox.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Player/PlayerCharacter.hpp"

#include "Robot.hpp"

#include "Tile.hpp"

namespace AAK
{
    namespace Forradia::Theme0::GameplayCore
    {
        void BattleSystem::Update()
        {
            if (m_targetedRobot == nullptr)
            {
                return;
            }

            auto worldArea{_<World>().GetCurrentWorldArea()};

            auto worldAreaSize{worldArea->GetSize()};

            auto &robots{worldArea->GetRobotsMirrorRef()};

            auto robotCoordinates{robots.at(m_targetedRobot)};

            auto &player{_<PlayerCharacter>()};

            player.SetDestination({robotCoordinates.x, robotCoordinates.y});

            auto playerPosition{player.GetPosition()};

            auto dx{robotCoordinates.x - playerPosition.x};

            auto dy{robotCoordinates.y - playerPosition.y};

            auto attackRange{1.0f};

            if (dx * dx + dy * dy <= attackRange * attackRange)
            {
                auto now{GetTicks()};

                if (now >= player.GetTicksLastHitAnother() + InvertSpeed(player.GetAttackSpeed()))
                {
                    m_targetedRobot->Hit(1);

                    player.SetTicksLastHitAnother(now);

                    auto isKnockedOut{m_targetedRobot->IsKnockedOut()};

                    if (isKnockedOut)
                    {
                        _<GUIChatBox>().Print("You have knocked out the robot!");

                        _<PlayerCharacter>().AddExperience(10);

                        _<GUIChatBox>().Print("You have gained 10 experience!");

                        auto robotTile{worldArea->GetTile(robotCoordinates.x, robotCoordinates.y)};

                        robotTile->SetRobot(nullptr);

                        robots.erase(m_targetedRobot);

                        m_targetedRobot = nullptr;
                    }
                }
            }
        }
    }
}