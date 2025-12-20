/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUISystemMenu.hpp"
#include "Color2DRenderer.hpp"
#include "GUIButton.hpp"
#include "GUIChatBox.hpp"
#include "GameSaveFiles/GameSaving.hpp"

namespace Forradia::Theme0 {
  auto GUISystemMenu::Initialize() -> void {
    this->SetVisible(false);

    auto saveGameButton{std::make_shared<GUIButton>("GUIButtonSaveGame", 0.5f - 0.08f / 2, 0.5f,
                                                    0.08f, 0.05f, "Save game", [this] {
                                                      _<GUIChatBox>().Print("Saving game...");
                                                      _<GameSaving>().SaveGame();
                                                    })};

    this->AddChildComponent(saveGameButton);

    auto loadGameButton{std::make_shared<GUIButton>(
        "GUIButtonLoadGame", 0.5f - 0.08f / 2, 0.5f + 0.05f, 0.08f, 0.05f, "Load game", [this] {
          _<GUIChatBox>().Print("Loading game...");
          _<GameSaving>().LoadGame();
        })};

    this->AddChildComponent(loadGameButton);
  }

  auto GUISystemMenu::UpdateDerived() -> void {
    GUIComponent::UpdateDerived();

    //_<MouseInput>().GetLeftMouseButtonRef().Reset();
  }

  auto GUISystemMenu::RenderDerived() const -> void {
    GUIComponent::RenderDerived();

    _<Color2DRenderer>().DrawFilledRectangle(k_renderIDBackgroundColor, {1.0f, 0.0f, 0.7f, 0.5f},
                                             0.0f, 0.0f, 1.0f, 1.0f);
  }
}
