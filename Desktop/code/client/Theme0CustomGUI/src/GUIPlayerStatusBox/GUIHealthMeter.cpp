//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIHealthMeter.hpp"

#include "Player/PlayerCharacter.hpp"

namespace Forradia::Theme0
{
    void GUIHealthMeter::UpdateDerived()
    {
        GUIMeter::UpdateDerived();

        auto &playerCharacter{_<Theme0::GameplayCore::PlayerCharacter>()};

        auto health{playerCharacter.GetHealth()};

        auto maxHealth{playerCharacter.GetMaxHealth()};

        auto bounds{this->GetBounds()};

        m_filledPercentage = health / maxHealth;
    }

    float GUIHealthMeter::GetFilledPercentage() const
    {
        return m_filledPercentage;
    }
}