/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "PlayScene.hpp"
#include "GUI.hpp"
#include "GUIButton.hpp"
#include "GUIChatBox.hpp"
#include "GUIPanel.hpp"
#include "Image2DRenderer.hpp"
#include "SceneManager.hpp"

namespace Forradia::Theme0 {
    auto PlayScene::InitializeDerived() -> void {
        auto panel{std::make_shared<GUIPanel>("PlayScenePanel", 0.4f, 0.32f, 0.2f, 0.32f)};
        GetGUI()->AddChildComponent(panel);

        auto btnNewGame{std::make_shared<GUIButton>(
            "PlaySceneButtonNewGame", 0.45, 0.36, 0.1, 0.04, "New game",
            [] { Singleton<SceneManager>().GoToScene("WorldGenerationScene"); })};
        GetGUI()->AddChildComponent(btnNewGame);

        auto btnLoadGame{std::make_shared<GUIButton>("PlaySceneButtonLoadGame", 0.45f, 0.44f, 0.1f,
                                                     0.04f, "Load game", [] {})};
        GetGUI()->AddChildComponent(btnLoadGame);

        auto btnBack{std::make_shared<GUIButton>(
            "PlaySceneButtonBack", 0.45f, 0.56f, 0.1f, 0.04f, "Back",
            [] { Singleton<SceneManager>().GoToScene("MainMenuScene"); })};
        GetGUI()->AddChildComponent(btnBack);

        GetGUI()->AddChildComponent(SingletonPtr<GUIChatBox>());
    }

    auto PlayScene::RenderDerived() const -> void {
        Singleton<Image2DRenderer>().DrawImageByName(
            Hash("PlaySceneBackground"), "DefaultSceneBackground", 0.0f, 0.0f, 1.0f, 1.0f);
        Singleton<Image2DRenderer>().DrawImageAutoHeight(Hash("PlaySceneLogo"), "ForradiaLogo",
                                                         0.35f, 0.1f, 0.3f);
    }
}
