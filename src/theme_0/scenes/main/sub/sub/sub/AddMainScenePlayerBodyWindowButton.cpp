/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainScenePlayerBodyWindowButton.hpp"
#include "core/gui_core/GUI.hpp"
#include "core/gui_core/GUIButton.hpp"
#include "theme_0/theme_0_mechanics/gui/GUIPlayerBodyWindow.hpp"

namespace Forradia {
  void AddMainScenePlayerBodyWindowButton(SharedPtr<GUI> mainSceneGUI) {
    mainSceneGUI->AddChildComponent(std::make_shared<GUIButton>(
        0.78f, 0.9f, 0.05f, ConvertWidthToHeight(0.05f), "",
        [] { GetSingleton<GUIPlayerBodyWindow>().ToggleVisibility(); },
        "GUIButtonPlayerBodyBackground",
        "GUIButtonPlayerBodyHoveredBackground"));
  }
}