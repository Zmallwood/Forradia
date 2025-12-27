/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIWellBeingMeter.hpp"
    
    #include "Content/Essentials/Player/Player.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIWellBeingMeter::updateDerived() -> void
    {
        GUIMeter::updateDerived();

        /* Update the filled percentage of the well-being meter */ // clang-format off
            auto &player{Player::instance()};

            auto health{player.getWellBeing()};
            auto maxHealth{player.getMaxWellBeing()};

            m_filledPercentage = health / maxHealth;
        // clang-format on
    }

    auto GUIWellBeingMeter::getFilledPercentage() const -> float
    {
        return m_filledPercentage;
    }
}
