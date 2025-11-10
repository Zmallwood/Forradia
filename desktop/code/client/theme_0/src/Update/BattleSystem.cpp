//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "BattleSystem.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "PlayerCharacter.hpp"

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

        auto coordinate{robots.at(m_targetedRobot)};

        auto &player{_<PlayerCharacter>()};

        player.SetDestination(
            {coordinate.x, coordinate.y});
    }
}