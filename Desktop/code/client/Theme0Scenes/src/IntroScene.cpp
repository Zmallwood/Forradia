//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "IntroScene.hpp"
#include "Cursor.hpp"
#include "GUI.hpp"
#include "GUIChatBox.hpp"
#include "GUILabel.hpp"
#include "Image2DRenderer.hpp"
#include "Keyboard/KeyboardInput.hpp"
#include "Mouse/MouseInput.hpp"
#include "SceneManager.hpp"

namespace Forradia::Theme0 {
void IntroScene::InitializeDerived() {
  auto lbl{std::make_shared<GUILabel>("GUILabelIntroSceneStartText", 0.45f, 0.5f, 0.1f, 0.04f,
                                      "Press to start", true)};
  m_startText = GetGUI()->AddChildComponent(lbl);
}

void IntroScene::OnEnterDerived() {
  _<GUIChatBox>().Print("Game started.");
}

void IntroScene::UpdateDerived() {
  m_startText->SetVisible(GetTicks() % 800 < 400);
  _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);
  if (_<KeyboardInput>().AnyKeyIsPressedPickResult() ||
      _<MouseInput>().AnyMouseButtonIsPressedPickResult()) {
    _<SceneManager>().GoToScene("MainMenuScene");
  }
}

void IntroScene::RenderDerived() const {
  _<Image2DRenderer>().DrawImageByName(Hash("IntroSceneBackground"), "DefaultSceneBackground", 0.0f,
                                       0.0f, 1.0f, 1.0f);
  _<Image2DRenderer>().DrawImageAutoHeight(Hash("IntroSceneLogo"), "ForradiaLogo", 0.25f, 0.2f,
                                           0.5f);
}
}