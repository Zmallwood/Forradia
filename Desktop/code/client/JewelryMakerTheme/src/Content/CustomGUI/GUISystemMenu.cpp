/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUISystemMenu.hpp"
    #include "Content/Core/GameSaveFiles/GameSaving.hpp"
    #include "ForradiaEngine/GUICore/GUIButton.hpp"
    #include "ForradiaEngine/GUICore/GUIChatBox.hpp"
    #include "ForradiaEngine/Rendering/Colors/Color2DRenderer.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUISystemMenu::initialize() -> void
    {
        this->setVisible(false);

        /* Add the save game button */ // clang-format off
            auto saveGameButton{std::make_shared<GUIButton>(
                "GUIButtonSaveGame", 0.5f - 0.08f / 2, 0.5f, 0.08f, 0.05f, "Save game",
                [this]
                {
                    GUIChatBox::instance().print("Saving game...");
                    GameSaving::instance().saveGame();
                })};

            this->addChildComponent(saveGameButton);
        // clang-format on

        /* Add the load game button */ // clang-format off
            auto loadGameButton{std::make_shared<GUIButton>(
                "GUIButtonLoadGame", 0.5f - 0.08f / 2, 0.5f + 0.05f, 0.08f, 0.05f, "Load game",
                [this]
                {
                    GUIChatBox::instance().print("Loading game...");
                    GameSaving::instance().loadGame();
                })};

            this->addChildComponent(loadGameButton);
        // clang-format on
    }

    auto GUISystemMenu::updateDerived() -> void
    {
        GUIComponent::updateDerived();
    }

    auto GUISystemMenu::renderDerived() const -> void
    {
        GUIComponent::renderDerived();

        // Fill the background of the system menu with a semi-transparent pink color
        Color2DRenderer::instance().drawFilledRectangle(
            k_renderIDBackgroundColor, {1.0f, 0.0f, 0.7f, 0.5f}, 0.0f, 0.0f, 1.0f, 1.0f);
    }
}
