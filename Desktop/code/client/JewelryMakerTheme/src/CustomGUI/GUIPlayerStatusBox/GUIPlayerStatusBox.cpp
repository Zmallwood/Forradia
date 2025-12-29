/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIPlayerStatusBox.hpp"
#include <fmt/format.h>
#include "Math/experienceCalculations.hpp"
#include "Player/Player.hpp"
#include "ForradiaEngine/GUICore/GUILabel.hpp"
#include "ForradiaEngine/Rendering/Text/TextRenderer.hpp"
#include "GUIWellBeingMeter.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIPlayerStatusBox::initialize() -> void
    {
        constexpr RectF wellBeingMeterBounds{0.06F, 0.1F, 0.12F, 0.015F};

        auto wellBeingMeter{std::make_shared<GUIWellBeingMeter>(
            wellBeingMeterBounds.x, wellBeingMeterBounds.y, wellBeingMeterBounds.width,
            wellBeingMeterBounds.height)};

        this->addChildComponent(wellBeingMeter);

        constexpr RectF wellBeingValueTextLabelBounds{0.08F, 0.095F, 0.1F, 0.05F};

        m_wellBeingValueTextLabel = std::make_shared<GUILabel>(
            "GUILabelWellBeingValueText", wellBeingValueTextLabelBounds.x,
            wellBeingValueTextLabelBounds.y, wellBeingValueTextLabelBounds.width,
            wellBeingValueTextLabelBounds.height, "", false, Palette::getColor<hash("Black")>());

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

        auto experience{Player::instance().getExperience()};
        auto level{calculateCurrentLevel(experience)};

        TextRenderer::instance().drawString(k_renderIDNameString, Player::instance().getName(),
                                            bounds.x + k_margin, bounds.y + k_margin,
                                            FontSizes::_26);

        TextRenderer::instance().drawString(k_renderLevelString, fmt::format("Level: {}", level),
                                            bounds.x + k_margin, bounds.y + k_levelTextLabelY,
                                            FontSizes::_26, false, true);

        TextRenderer::instance().drawString(k_renderWellBeingString, "WB", bounds.x + k_margin,
                                            bounds.y + k_wellBeingTextLabelY, FontSizes::_20);
    }
}
