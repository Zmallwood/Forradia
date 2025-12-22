/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIExperienceBar.hpp"
#include "Math/ExperienceCalculations.hpp"
#include "Player/Player.hpp"

namespace Forradia::Theme0 {
    auto GUIExperienceBar::UpdateDerived() -> void {
        GUIMeter::UpdateDerived();

        auto &player{Player::Instance()};
        auto experience{player.GetExperience()};
        auto levelProgress{CalculateFractionalExperienceProgress(experience)};
        m_filledPercentage = levelProgress;
    }

    auto GUIExperienceBar::GetFilledPercentage() const -> float {
        return m_filledPercentage;
    }
}
