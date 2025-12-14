//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO

#include "Quests.hpp"
#include "GUIChatBox.hpp"
#include "Player/PlayerCharacter.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void MoveQuest::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numSteps{0};

        for (auto &action : playerActions)
        {
            if (action == PlayerActionTypes::MoveNorth || action == PlayerActionTypes::MoveEast ||
                action == PlayerActionTypes::MoveSouth || action == PlayerActionTypes::MoveWest)
            {
                numSteps++;
            }
        }
        m_numStepsLeft = 3 - numSteps;
        if (numSteps >= 3)
        {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Movement. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }

        return;
    }

    String MoveQuest::GetStatus() const
    {
        return "Movements left: " + std::to_string(m_numStepsLeft);
    }

    void ForageQuest::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        for (auto &action : playerActions)
        {
            if (action == PlayerActionTypes::Forage)
            {
                isCompleted = true;
                _<GUIChatBox>().Print("Quest completed: Forage. Obtained 50 XP.");
                _<PlayerCharacter>().AddExperience(50);
            }
        }
    }

    String ForageQuest::GetStatus() const
    {
        return "Forages left: 1";
    }
}