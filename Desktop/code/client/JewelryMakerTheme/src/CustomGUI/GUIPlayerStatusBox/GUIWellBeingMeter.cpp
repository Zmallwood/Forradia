/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIWellBeingMeter.hpp"
#include "Player/Player.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIWellBeingMeter::updateDerived() -> void
    {
        GUIMeter::updateDerived();

        auto &player{Player::instance()};

        auto health{player.getWellBeing()};
        auto maxHealth{player.getMaxWellBeing()};

        m_filledPercentage = health / maxHealth;
    }

    auto GUIWellBeingMeter::getFilledPercentage() const -> float
    {
        return m_filledPercentage;
    }
}
