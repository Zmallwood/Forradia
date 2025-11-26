//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIPlayerStatusBox.hpp"

#include "TextRenderer.hpp"

#include "Player/PlayerCharacter.hpp"

#include "Math/ExperienceCalculations.hpp"

#include "GUIHealthMeter.hpp"

#include "GUILabel.hpp"

namespace Forradia::Theme0
{
    void GUIPlayerStatusBox::Initialize()
    {
        // Create the health meter.

        auto healthMeter{std::make_shared<GUIHealthMeter>(0.06f, 0.1f, 0.12f, 0.015f)};

        // Add the name text label to this panel.

        this->AddChildComponent(healthMeter);

        m_healthValueTextLabel =
            std::make_shared<GUILabel>("GUILabelHealthValueText", 0.08f, 0.095f, 0.1f, 0.05f, "",
                                       false, Palette::GetColor<Hash("Black")>());

        this->AddChildComponent(m_healthValueTextLabel);
    }

    void GUIPlayerStatusBox::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        auto health{_<Theme0::GameplayCore::PlayerCharacter>().GetHealth()};

        auto maxHealth{_<Theme0::GameplayCore::PlayerCharacter>().GetMaxHealth()};

        m_healthValueTextLabel->SetText(fmt::format("{} / {}", health, maxHealth));
    }

    void GUIPlayerStatusBox::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{this->GetBounds()};

        _<TextRenderer>().DrawString(k_renderIDNameString,
                                     _<Theme0::GameplayCore::PlayerCharacter>().GetName(),
                                     bounds.x + 0.01f, bounds.y + 0.01f, FontSizes::_26);

        auto experience{_<Theme0::GameplayCore::PlayerCharacter>().GetExperience()};

        auto level{GameplayCore::CalculateCurrentLevel(experience)};

        _<TextRenderer>().DrawString(k_renderLevelString, fmt::format("Level: {}", level),
                                     bounds.x + 0.01f, bounds.y + 0.04f, FontSizes::_26, false,
                                     true);

        _<TextRenderer>().DrawString(k_renderHealthString, "Health", bounds.x + 0.01f,
                                     bounds.y + 0.095f, FontSizes::_20);
    }
}