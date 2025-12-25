/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIExperienceBar.hpp"
    #include "Content/Essentials/Math/ExperienceCalculations.hpp"
    #include "Content/Essentials/Player/Player.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
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
