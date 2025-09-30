/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "IntroScene.hpp"
#include "core/cursor/Cursor.hpp"
#include "core/gui_core/GUI.hpp"
#include "core/gui_core/GUILabel.hpp"
#include "core/gui_core/GUITextConsole.hpp"
#include "core/input/keyboard/KeyboardInput.hpp"
#include "core/input/mouse/MouseInput.hpp"
#include "core/rendering/images/ImageRenderer.hpp"
#include "core/scenes_core/SceneManager.hpp"

namespace Forradia {
  void IntroScene::InitializeDerived() {
    m_startText = GetGUI()->AddChildComponent(std::make_shared<GUILabel>(
        0.45f, 0.5f, 0.1f, 0.04f, "Press to start", true));
  }

  void IntroScene::OnEnterDerived() {
    GetSingleton<GUITextConsole>().Print("Game started.");
  }

  void IntroScene::UpdateDerived() {
    m_startText->SetVisible((GetTicks() % 800) < 400);

    GetSingleton<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

    if (GetSingleton<KeyboardInput>().AnyKeyIsPressedPickResult() ||
        GetSingleton<MouseInput>().AnyMouseButtonIsPressedPickResult()) {
      GetSingleton<SceneManager>().GoToScene("MainMenuScene");
    }
  }

  void IntroScene::RenderDerived() const {
    GetSingleton<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f, 0.0f, 1.0f,
                                 1.0f);
    GetSingleton<ImageRenderer>().DrawImageWithAutoHeight("ForradiaLogo", 0.25f, 0.2f,
                                               0.5f);
  }
}
