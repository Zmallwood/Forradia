/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MainMenuScene.hpp"
#include "Engine.hpp"
#include "GUI.hpp"
#include "GUIButton.hpp"
#include "GUIChatBox.hpp"
#include "GUIPanel.hpp"
#include "Image2DRenderer.hpp"
#include "SceneManager.hpp"

namespace Forradia::Theme0 {
void MainMenuScene::InitializeDerived() {
  auto panel{std::make_shared<GUIPanel>("MainMenuScenePanel", 0.4f, 0.32f, 0.2f, 0.2f)};
  GetGUI()->AddChildComponent(panel);

  auto btnPlay{std::make_shared<GUIButton>("MainMenuSceneButtonPlay", 0.45f, 0.36f, 0.1f, 0.04f,
                                           "Play",
                                           [] { _<SceneManager>().GoToScene("PlayScene"); })};
  GetGUI()->AddChildComponent(btnPlay);

  auto btnQuit{std::make_shared<GUIButton>("MainMenuSceneButtonQuit", 0.45f, 0.44f, 0.1f, 0.04f,
                                           "Quit", [] { _<Engine>().Stop(); })};
  GetGUI()->AddChildComponent(btnQuit);

  GetGUI()->AddChildComponent(__<GUIChatBox>());
}

void MainMenuScene::RenderDerived() const {
  _<Image2DRenderer>().DrawImageByName(Hash("IntroSceneBackground"), "DefaultSceneBackground", 0.0f,
                                       0.0f, 1.0f, 1.0f);
  _<Image2DRenderer>().DrawImageAutoHeight(Hash("IntroSceneLogo"), "ForradiaLogo", 0.35f, 0.1f,
                                           0.3f);
}
}