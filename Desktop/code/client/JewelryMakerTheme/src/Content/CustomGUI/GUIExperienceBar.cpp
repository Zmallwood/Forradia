/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIExperienceBar.hpp"
    #include "Content/Essentials/Math/ExperienceCalculations.hpp"
    #include "Content/Essentials/Player/Player.hpp"
// clang-format on

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
