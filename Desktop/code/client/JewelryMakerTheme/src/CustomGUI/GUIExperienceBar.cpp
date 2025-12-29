/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIExperienceBar.hpp"
#include "Math/experience_calculations.hpp"
#include "Player/Player.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIExperienceBar::updateDerived() -> void
    {
        GUIMeter::updateDerived();

        auto experience{Player::instance().getExperience()};

        m_filledPercentage = calculateFractionalExperienceProgress(experience);
    }

    auto GUIExperienceBar::getFilledPercentage() const -> float
    {
        return m_filledPercentage;
    }
}
