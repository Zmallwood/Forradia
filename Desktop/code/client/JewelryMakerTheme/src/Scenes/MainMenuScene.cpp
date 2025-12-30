/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "MainMenuScene.hpp"
#include "ForradiaEngine/Engine.hpp"
#include "ForradiaEngine/GUICore/GUI.hpp"
#include "ForradiaEngine/GUICore/GUIButton.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"
#include "ForradiaEngine/GUICore/GUIPanel.hpp"
#include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
#include "ForradiaEngine/Assets/Audio/AudioBank.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto MainMenuScene::initializeDerived() -> void
    {
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto panel{std::make_shared<GUIPanel>("MainMenuScenePanel", 0.4F, 0.32F, 0.2F, 0.2F)};

        getGUI()->addChildComponent(panel);

        // NOLINTBEGIN(readability-magic-numbers)
        auto btnPlay{std::make_shared<GUIButton>(
            "MainMenuSceneButtonPlay", 0.45F, 0.36F, 0.1F, 0.04F, "",
            [] { SceneManager::instance().goToScene("PlayScene"); }, "GUIButtonPlayBackground",
            "GUIButtonPlayHoveredBackground")};
        // NOLINTEND(readability-magic-numbers)

        getGUI()->addChildComponent(btnPlay);

        // NOLINTBEGIN(readability-magic-numbers)
        auto btnQuit{std::make_shared<GUIButton>(
            "MainMenuSceneButtonQuit", 0.45F, 0.44F, 0.1F, 0.04F, "",
            [] { Engine::instance().stop(); }, "GUIButtonQuitBackground",
            "GUIButtonQuitHoveredBackground")};
        // NOLINTEND(readability-magic-numbers)

        getGUI()->addChildComponent(btnQuit);

        getGUI()->addChildComponent(GUIChatBox::instancePtr());

        auto btnToggleMuteMusic{std::make_shared<GUIButton>(
            "MainMenuSceneButtonToggleMuteMusic", 0.95F, 0.95F, 0.1F, 0.04F, "",
            [] { AudioBank::instance().toggleMuteMusic(); })};

        getGUI()->addChildComponent(btnToggleMuteMusic);
    }

    auto MainMenuScene::renderDerived() const -> void
    {
        // NOLINTBEGIN(readability-magic-numbers)
        Image2DRenderer::instance().drawImageByName(
            hash("MainMenuSceneBackground"), "DefaultSceneBackground", 0.0F, 0.0F, 1.0F, 1.0F);
        // NOLINTEND(readability-magic-numbers)

        // NOLINTBEGIN(readability-magic-numbers)
        Image2DRenderer::instance().drawImageAutoHeight(hash("MainMenuSceneLogo"),
                                                        "JewelryMakerLogo", 0.35F, 0.1F, 0.3F);
        // NOLINTEND(readability-magic-numbers)
    }
}
