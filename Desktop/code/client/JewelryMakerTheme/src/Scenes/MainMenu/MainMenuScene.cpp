/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "MainMenuScene.hpp"
    #include "ForradiaEngine/Engine.hpp"
    #include "ForradiaEngine/GUICore/GUI.hpp"
    #include "ForradiaEngine/GUICore/GUIButton.hpp"
    #include "ForradiaEngine/GUICore/GUIChatBox.hpp"
    #include "ForradiaEngine/GUICore/GUIPanel.hpp"
    #include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
    #include "ForradiaEngine/ScenesCore/SceneManager.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto MainMenuScene::initializeDerived() -> void
    {
        auto panel{std::make_shared<GUIPanel>("MainMenuScenePanel", 0.4f, 0.32f, 0.2f, 0.2f)};

        getGUI()->addChildComponent(panel);

        /* Adding Play button */ // clang-format off
            auto btnPlay{std::make_shared<GUIButton>(
                "MainMenuSceneButtonPlay", 0.45f, 0.36f, 0.1f, 0.04f, "",
                [] { SceneManager::instance().goToScene("PlayScene"); }, "GUIButtonPlayBackground",
                "GUIButtonPlayHoveredBackground")};
                
            getGUI()->addChildComponent(btnPlay);
        // clang-format on

        /* Adding Quit button */ // clang-format off
            auto btnQuit{std::make_shared<GUIButton>(
                "MainMenuSceneButtonQuit", 0.45f, 0.44f, 0.1f, 0.04f, "",
                [] { Engine::instance().stop(); }, "GUIButtonQuitBackground",
                "GUIButtonQuitHoveredBackground")};
                
            getGUI()->addChildComponent(btnQuit);
        // clang-format on

        getGUI()->addChildComponent(GUIChatBox::instancePtr());
    }

    auto MainMenuScene::renderDerived() const -> void
    {
        Image2DRenderer::instance().drawImageByName(
            hash("MainMenuSceneBackground"), "DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);

        Image2DRenderer::instance().drawImageAutoHeight(hash("MainMenuSceneLogo"),
                                                        "JewelryMakerLogo", 0.35f, 0.1f, 0.3f);
    }
}
