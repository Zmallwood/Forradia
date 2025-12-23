/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIExperienceBar.hpp"
#include "Math/ExperienceCalculations.hpp"
#include "Player/Player.hpp"

namespace Forradia::Theme0
{
    auto GUIExperienceBar::updateDerived() -> void
    {
        GUIMeter::updateDerived();

        auto &player{Player::instance()};

        auto experience{player.getExperience()};

        auto levelProgress{calculateFractionalExperienceProgress(experience)};

        m_filledPercentage = levelProgress;
    }

    auto GUIExperienceBar::getFilledPercentage() const -> float
    {
        return m_filledPercentage;
    }
}
