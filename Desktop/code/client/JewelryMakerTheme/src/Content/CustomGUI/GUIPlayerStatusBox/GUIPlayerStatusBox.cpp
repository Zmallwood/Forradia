/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIPlayerStatusBox.hpp"
    
    #include "Content/Essentials/Math/ExperienceCalculations.hpp"
    #include "Content/Essentials/Player/Player.hpp"
    #include "ForradiaEngine/GUICore/GUILabel.hpp"
    #include "ForradiaEngine/Rendering/Text/TextRenderer.hpp"
    #include "GUIWellBeingMeter.hpp"
    #include <fmt/format.h>
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIPlayerStatusBox::initialize() -> void
    {
        /* Add the well-being meter */ // clang-format off
                auto wellBeingMeter{std::make_shared<GUIWellBeingMeter>(0.06F, 0.1F, 0.12F, 0.015F)};

                this->addChildComponent(wellBeingMeter);
        // clang-format on

        /* Add the well-being value text label */ // clang-format off
            m_wellBeingValueTextLabel =
                std::make_shared<GUILabel>("GUILabelWellBeingValueText", 0.08f, 0.095f, 0.1f, 0.05f, "",
                                        false, Palette::getColor<hash("Black")>());

            this->addChildComponent(m_wellBeingValueTextLabel);
        // clang-format on
    }

    auto GUIPlayerStatusBox::updateDerived() -> void
    {
        GUIPanel::updateDerived();

        /* Update the well-being value text label */ // clang-format off
            auto wellBeing{Player::instance().getWellBeing()};
            auto maxWellBeing{Player::instance().getMaxWellBeing()};

            m_wellBeingValueTextLabel->setText(fmt::format("{} / {}", wellBeing, maxWellBeing));
        // clang-format on
    }

    auto GUIPlayerStatusBox::renderDerived() const -> void
    {
        GUIPanel::renderDerived();

        auto bounds{this->getBounds()};

        auto experience{Player::instance().getExperience()};
        auto level{calculateCurrentLevel(experience)};

        /* Draw the status box components */ // clang-format off
            TextRenderer::instance().drawString(k_renderIDNameString, Player::instance().getName(),
                                                bounds.x + 0.01f, bounds.y + 0.01f, FontSizes::_26);

            TextRenderer::instance().drawString(k_renderLevelString, fmt::format("Level: {}", level),
                                                bounds.x + 0.01f, bounds.y + 0.04f, FontSizes::_26,
                                                false, true);
                                                
            TextRenderer::instance().drawString(k_renderWellBeingString, "WB", bounds.x + 0.01f,
                                                bounds.y + 0.095f, FontSizes::_20);
        // clang-format on
    }
}
