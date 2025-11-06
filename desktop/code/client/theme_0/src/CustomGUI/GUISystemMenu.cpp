//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUISystemMenu.hpp"

#include "Mouse/MouseInput.hpp"

#include "Color2DRenderer.hpp"

#include "GUIButton.hpp"

#include "GUIChatBox.hpp"

namespace Forradia::Theme0
{
    void GUISystemMenu::Initialize()
    {
        this->SetVisible(false);

        auto saveGameButton{std::make_shared<GUIButton>(
            "GUIButtonSaveGame", 0.5f - 0.08f / 2, 0.5f,
            0.08f, 0.05f, "Save game", [this]
            { _<GUIChatBox>().Print("Saving game..."); })};

        this->AddChildComponent(saveGameButton);
    }

    void GUISystemMenu::UpdateDerived()
    {
        GUIComponent::UpdateDerived();

        _<MouseInput>().GetLeftMouseButtonRef().Reset();
    }

    void GUISystemMenu::RenderDerived() const
    {
        GUIComponent::RenderDerived();

        _<Color2DRenderer>().DrawFilledRectangle(
            k_renderIDBackgroundColor,
            {1.0f, 0.0f, 0.7f, 0.5f}, 0.0f, 0.0f, 1.0f,
            1.0f);
    }
}