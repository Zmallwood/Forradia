/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUITimedActionBar.hpp"
#include "actions.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUITimedActionBar::update() -> void
    {
        constexpr float EPSILON = 1e-6f;

        if (std::fabs(m_filledPercentage) < EPSILON)
        {
            this->setVisible(false);
        }
        else
        {
            this->setVisible(true);
        }

        for (auto &childComponent : std::ranges::reverse_view(this->getChildComponents()))
        {
            childComponent->update();
        }

        this->updateDerived();
    }

    auto GUITimedActionBar::updateDerived() -> void
    {
        GUIMeter::updateDerived();

        m_filledPercentage = getTimedActionProgress();
    }

    auto GUITimedActionBar::getFilledPercentage() const -> float
    {
        return m_filledPercentage;
    }
}
