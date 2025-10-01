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

namespace forr {
  void intro_scene::InitializeDerived() {
    m_startText = GetGUI()->AddChildComponent(std::make_shared<gui_label>(
        0.45f, 0.5f, 0.1f, 0.04f, "Press to start", true));
  }

  void intro_scene::OnEnterDerived() {
    GetSingleton<gui_text_console>().Print("Game started.");
  }

  void intro_scene::UpdateDerived() {
    m_startText->SetVisible((GetTicks() % 800) < 400);

    GetSingleton<cursor>().SetCursorStyle(cursor_styles::HoveringClickableGUI);

    if (GetSingleton<keyboard_input>().AnyKeyIsPressedPickResult() ||
        GetSingleton<mouse_input>().AnyMouseButtonIsPressedPickResult()) {
      GetSingleton<scene_manager>().GoToScene("MainMenuScene");
    }
  }

  void intro_scene::RenderDerived() const {
    GetSingleton<image_renderer>().DrawImage("DefaultSceneBackground", 0.0f,
                                             0.0f, 1.0f, 1.0f);
    GetSingleton<image_renderer>().DrawImageWithAutoHeight("ForradiaLogo",
                                                           0.25f, 0.2f, 0.5f);
  }
}
