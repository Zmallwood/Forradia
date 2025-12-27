/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "PlayScene.hpp"
    
    #include "ForradiaEngine/GUICore/GUI.hpp"
    #include "ForradiaEngine/GUICore/GUIButton.hpp"
    #include "ForradiaEngine/GUICore/GUIChatBox.hpp"
    #include "ForradiaEngine/GUICore/GUIPanel.hpp"
    #include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto PlayScene::initializeDerived() -> void
    {
        auto panel{std::make_shared<GUIPanel>("PlayScenePanel", 0.4f, 0.32f, 0.2f, 0.32f)};

        getGUI()->addChildComponent(panel);

        /* Adding New Game button */ // clang-format off
            auto buttonNewGame{std::make_shared<GUIButton>(
                "PlaySceneButtonNewGame", 0.45, 0.36, 0.1, 0.04, "",
                [] { SceneManager::instance().goToScene("WorldGenerationScene"); },
                "GUIButtonNewGameBackground", "GUIButtonNewGameHoveredBackground")};

            getGUI()->addChildComponent(buttonNewGame);
        // clang-format on

        /* Adding Load Game button */ // clang-format off
            auto buttonLoadGame{std::make_shared<GUIButton>(
                "PlaySceneButtonLoadGame", 0.45f, 0.44f, 0.1f, 0.04f, "", [] {},
                "GUIButtonLoadGameBackground", "GUIButtonLoadGameHoveredBackground")};

            getGUI()->addChildComponent(buttonLoadGame);
        // clang-format on

        /* Adding Back button */ // clang-format off
            auto buttonBack{std::make_shared<GUIButton>(
                "PlaySceneButtonBack", 0.45f, 0.56f, 0.1f, 0.04f, "",
                [] { SceneManager::instance().goToScene("MainMenuScene"); }, "GUIButtonBackBackground",
                "GUIButtonBackHoveredBackground")};

            getGUI()->addChildComponent(buttonBack);
        // clang-format on

        getGUI()->addChildComponent(GUIChatBox::instancePtr());
    }

    auto PlayScene::renderDerived() const -> void
    {
        Image2DRenderer::instance().drawImageByName(
            hash("PlaySceneBackground"), "DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);

        Image2DRenderer::instance().drawImageAutoHeight(hash("PlaySceneLogo"), "JewelryMakerLogo",
                                                        0.35f, 0.1f, 0.3f);
    }
}
