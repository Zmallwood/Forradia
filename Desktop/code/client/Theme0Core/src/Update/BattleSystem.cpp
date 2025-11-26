//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "BattleSystem.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Player/PlayerCharacter.hpp"

#include "Robot.hpp"

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

        auto dx {robotCoordinates.x - playerPosition.x};

        auto dy {robotCoordinates.y - playerPosition.y};

        auto attackRange{1.0f};

        if (dx*dx + dy*dy <= attackRange*attackRange)
        {
            m_targetedRobot->TakeDamage(1);
        }
    }
}