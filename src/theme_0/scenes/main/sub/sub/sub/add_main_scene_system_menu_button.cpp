/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "add_main_scene_system_menu_button.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_button.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_system_menu.hpp"

namespace forr {
  void AddMainSceneSystemMenuButton(s_ptr<gui> mainSceneGUI) {
    mainSceneGUI->AddChildComponent(std::make_shared<gui_button>(
        0.92f, 0.9f, 0.05f, ConvertWidthToHeight(0.05f), "",
        [] { GetSingleton<gui_system_menu>().ToggleVisibility(); },
        "GUIButtonSystemBackground", "GUIButtonSystemHoveredBackground"));
  }
}