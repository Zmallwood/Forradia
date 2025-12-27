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
            constexpr RectF saveGameButtonBounds{0.5F - 0.08F / 2, 0.5F, 0.08F, 0.05F};

            auto saveGameButton{std::make_shared<GUIButton>(
                "GUIButtonSaveGame", saveGameButtonBounds.x, saveGameButtonBounds.y,
                saveGameButtonBounds.width, saveGameButtonBounds.height, "Save game",
                [this]
                {
                    GUIChatBox::instance().print("Saving game...");
                    GameSaving::saveGame();
                })};

            this->addChildComponent(saveGameButton);
        // clang-format on

        /* Add the load game button */ // clang-format off
            constexpr RectF loadGameButtonBounds{0.5F - 0.08F / 2, 0.5F + 0.055F, 0.08F, 0.05F};

            auto loadGameButton{std::make_shared<GUIButton>(
                "GUIButtonLoadGame", loadGameButtonBounds.x, loadGameButtonBounds.y,
                loadGameButtonBounds.width, loadGameButtonBounds.height, "Load game",
                [this]
                {
                    GUIChatBox::instance().print("Loading game...");
                    GameSaving::loadGame();
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

        constexpr Color backgroundColor{1.0F, 0.0F, 0.7F, 0.5F};
        constexpr RectF backgroundBounds{0.0F, 0.0F, 1.0F, 1.0F};

        Color2DRenderer::instance().drawFilledRectangle(
            k_renderIDBackgroundColor, backgroundColor, backgroundBounds.x, backgroundBounds.y,
            backgroundBounds.width, backgroundBounds.height);
    }
}
