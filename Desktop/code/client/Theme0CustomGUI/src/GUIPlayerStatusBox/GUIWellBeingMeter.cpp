/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIWellBeingMeter.hpp"
#include "Content/Essentials/Player/Player.hpp"

namespace Forradia::Theme0
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
