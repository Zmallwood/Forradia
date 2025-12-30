/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "PlayScene.hpp"
#include "ForradiaEngine/GUICore/GUI.hpp"
#include "ForradiaEngine/GUICore/GUIButton.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"
#include "ForradiaEngine/GUICore/GUIPanel.hpp"
#include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
#include "ForradiaEngine/Assets/Audio/AudioBank.hpp"
#include "ForradiaEngine/Devices/SDLDevice.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto PlayScene::initializeDerived() -> void
    {
        // NOLINTBEGIN(readability-magic-numbers)
        auto panel{std::make_shared<GUIPanel>("PlayScenePanel", 0.4F, 0.32F, 0.2F, 0.32F)};
        // NOLINTEND(readability-magic-numbers)

        getGUI()->addChildComponent(panel);

        // NOLINTBEGIN(readability-magic-numbers)
        auto buttonNewGame{std::make_shared<GUIButton>(
            "PlaySceneButtonNewGame", 0.45F, 0.36F, 0.1F, 0.04F, "",
            [] { SceneManager::instance().goToScene("WorldGenerationScene"); },
            "GUIButtonNewGameBackground", "GUIButtonNewGameHoveredBackground")};
        // NOLINTEND(readability-magic-numbers)
        getGUI()->addChildComponent(buttonNewGame);

        // NOLINTBEGIN(readability-magic-numbers)
        auto buttonLoadGame{std::make_shared<GUIButton>(
            "PlaySceneButtonLoadGame", 0.45F, 0.44F, 0.1F, 0.04F, "", [] {},
            "GUIButtonLoadGameBackground", "GUIButtonLoadGameHoveredBackground")};
        // NOLINTEND(readability-magic-numbers)
        getGUI()->addChildComponent(buttonLoadGame);

        // NOLINTBEGIN(readability-magic-numbers)
        auto buttonBack{std::make_shared<GUIButton>(
            "PlaySceneButtonBack", 0.45F, 0.56F, 0.1F, 0.04F, "",
            [] { SceneManager::instance().goToScene("MainMenuScene"); }, "GUIButtonBackBackground",
            "GUIButtonBackHoveredBackground")};
        // NOLINTEND(readability-magic-numbers)

        getGUI()->addChildComponent(buttonBack);

        getGUI()->addChildComponent(GUIChatBox::instancePtr());

        m_btnToggleMuteMusic = std::make_shared<GUIButton>(
            "MainMenuSceneButtonToggleMuteMusic", 0.95F, 0.93F, 0.04F,
            convertWidthToHeight(0.04F, SDLDevice::instance().getWindow()), "",
            [this]
            {
                AudioBank::instance().toggleMuteMusic();

                if (AudioBank::instance().getMusicMuted())
                {
                    m_btnToggleMuteMusic->setBackgroundImage("GUIButtonUnmuteMusicBackground");
                    m_btnToggleMuteMusic->setHoveredBackgroundImage(
                        "GUIButtonUnmuteMusicHoveredBackground");
                }
                else
                {
                    m_btnToggleMuteMusic->setBackgroundImage("GUIButtonMuteMusicBackground");
                    m_btnToggleMuteMusic->setHoveredBackgroundImage(
                        "GUIButtonMuteMusicHoveredBackground");
                }
            },
            "GUIButtonMuteMusicBackground", "GUIButtonMuteMusicHoveredBackground");

        getGUI()->addChildComponent(m_btnToggleMuteMusic);
    }

    auto PlayScene::renderDerived() const -> void
    {
        // NOLINTBEGIN(readability-magic-numbers)
        Image2DRenderer::instance().drawImageByName(
            hash("PlaySceneBackground"), "DefaultSceneBackground", 0.0F, 0.0F, 1.0F, 1.0F);
        // NOLINTEND(readability-magic-numbers)

        // NOLINTBEGIN(readability-magic-numbers)
        Image2DRenderer::instance().drawImageAutoHeight(hash("PlaySceneLogo"), "JewelryMakerLogo",
                                                        0.35F, 0.1F, 0.3F);
        // NOLINTEND(readability-magic-numbers)
    }
}
