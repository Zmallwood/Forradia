/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIPlayerStatusBox.hpp"
#include "GUICore/GUILabel.hpp"
#include "GUIWellBeingMeter.hpp"
#include "Math/ExperienceCalculations.hpp"
#include "Player/Player.hpp"
#include "TextRenderer.hpp"

namespace Forradia::Theme0
{
    auto GUIPlayerStatusBox::initialize() -> void
    {
        auto wellBeingMeter{std::make_shared<GUIWellBeingMeter>(0.06f, 0.1f, 0.12f, 0.015f)};

        this->addChildComponent(wellBeingMeter);

        m_wellBeingValueTextLabel =
            std::make_shared<GUILabel>("GUILabelWellBeingValueText", 0.08f, 0.095f, 0.1f, 0.05f, "",
                                       false, Palette::getColor<hash("Black")>());

        this->addChildComponent(m_wellBeingValueTextLabel);
    }

    auto GUIPlayerStatusBox::updateDerived() -> void
    {
        GUIPanel::updateDerived();

        auto wellBeing{Player::instance().getWellBeing()};
        auto maxWellBeing{Player::instance().getMaxWellBeing()};

        m_wellBeingValueTextLabel->setText(fmt::format("{} / {}", wellBeing, maxWellBeing));
    }

    auto GUIPlayerStatusBox::renderDerived() const -> void
    {
        GUIPanel::renderDerived();

        auto bounds{this->getBounds()};

        TextRenderer::instance().drawString(k_renderIDNameString, Player::instance().getName(),
                                            bounds.x + 0.01f, bounds.y + 0.01f, FontSizes::_26);

        auto experience{Player::instance().getExperience()};
        auto level{calculateCurrentLevel(experience)};

        TextRenderer::instance().drawString(k_renderLevelString, fmt::format("Level: {}", level),
                                            bounds.x + 0.01f, bounds.y + 0.04f, FontSizes::_26,
                                            false, true);
        TextRenderer::instance().drawString(k_renderWellBeingString, "WB", bounds.x + 0.01f,
                                            bounds.y + 0.095f, FontSizes::_20);
    }
}
