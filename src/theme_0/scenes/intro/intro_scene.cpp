/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "intro_scene.hpp"
#include "core/cursor/cursor.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_label.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/rendering/images/image_renderer.hpp"
#include "core/scenes_core/scene_manager.hpp"

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
    GetSingleton<ImageRenderer>().DrawImage("DefaultSceneBackground", 0.0f,
                                            0.0f, 1.0f, 1.0f);
    GetSingleton<ImageRenderer>().DrawImageWithAutoHeight("ForradiaLogo", 0.25f,
                                                          0.2f, 0.5f);
  }
}
