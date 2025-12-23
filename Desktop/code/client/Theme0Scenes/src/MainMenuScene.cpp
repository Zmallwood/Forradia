/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "MainMenuScene.hpp"
#include "Engine.hpp"
#include "GUI.hpp"
#include "GUIButton.hpp"
#include "GUIChatBox.hpp"
#include "GUIPanel.hpp"
#include "Image2DRenderer.hpp"
#include "SceneManager.hpp"

namespace Forradia::Theme0
{
    auto MainMenuScene::initializeDerived() -> void
    {
        auto panel{std::make_shared<GUIPanel>("MainMenuScenePanel", 0.4f, 0.32f, 0.2f, 0.2f)};
        getGUI()->addChildComponent(panel);

        auto btnPlay{std::make_shared<GUIButton>(
            "MainMenuSceneButtonPlay", 0.45f, 0.36f, 0.1f, 0.04f, "",
            [] { SceneManager::instance().goToScene("PlayScene"); }, "GUIButtonPlayBackground",
            "GUIButtonPlayHoveredBackground")};
        getGUI()->addChildComponent(btnPlay);

        auto btnQuit{std::make_shared<GUIButton>(
            "MainMenuSceneButtonQuit", 0.45f, 0.44f, 0.1f, 0.04f, "",
            [] { Engine::instance().stop(); }, "GUIButtonQuitBackground",
            "GUIButtonQuitHoveredBackground")};
        getGUI()->addChildComponent(btnQuit);

        getGUI()->addChildComponent(GUIChatBox::instancePtr());
    }

    auto MainMenuScene::renderDerived() const -> void
    {
        Image2DRenderer::instance().drawImageByName(
            hash("MainMenuSceneBackground"), "DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);

        Image2DRenderer::instance().drawImageAutoHeight(hash("MainMenuSceneLogo"), "ForradiaLogo",
                                                        0.35f, 0.1f, 0.3f);
    }
}
