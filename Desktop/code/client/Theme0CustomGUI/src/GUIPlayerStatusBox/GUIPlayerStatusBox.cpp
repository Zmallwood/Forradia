/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIPlayerStatusBox.hpp"
#include "GUILabel.hpp"
#include "GUIWellBeingMeter.hpp"
#include "Math/ExperienceCalculations.hpp"
#include "Player/Player.hpp"
#include "TextRenderer.hpp"

namespace Forradia::Theme0
{
    auto GUIPlayerStatusBox::Initialize() -> void
    {
        auto wellBeingMeter{std::make_shared<GUIWellBeingMeter>(0.06f, 0.1f, 0.12f, 0.015f)};
        this->AddChildComponent(wellBeingMeter);

        m_wellBeingValueTextLabel =
            std::make_shared<GUILabel>("GUILabelWellBeingValueText", 0.08f, 0.095f, 0.1f, 0.05f, "",
                                       false, Palette::GetColor<Hash("Black")>());

        this->AddChildComponent(m_wellBeingValueTextLabel);
    }

    auto GUIPlayerStatusBox::UpdateDerived() -> void
    {
        GUIPanel::UpdateDerived();

        auto wellBeing{Player::Instance().GetWellBeing()};
        auto maxWellBeing{Player::Instance().GetMaxWellBeing()};

        m_wellBeingValueTextLabel->SetText(fmt::format("{} / {}", wellBeing, maxWellBeing));
    }

    auto GUIPlayerStatusBox::RenderDerived() const -> void
    {
        GUIPanel::RenderDerived();

        auto bounds{this->GetBounds()};

        TextRenderer::Instance().DrawString(k_renderIDNameString, Player::Instance().GetName(),
                                            bounds.x + 0.01f, bounds.y + 0.01f, FontSizes::_26);

        auto experience{Player::Instance().GetExperience()};
        auto level{CalculateCurrentLevel(experience)};

        TextRenderer::Instance().DrawString(k_renderLevelString, fmt::format("Level: {}", level),
                                            bounds.x + 0.01f, bounds.y + 0.04f, FontSizes::_26,
                                            false, true);
        TextRenderer::Instance().DrawString(k_renderWellBeingString, "WB", bounds.x + 0.01f,
                                            bounds.y + 0.095f, FontSizes::_20);
    }
}
