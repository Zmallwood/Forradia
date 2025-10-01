/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "add_main_scene_inventory_window_button.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_button.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_inventory_window.hpp"

namespace forr {
  void add_main_scene_inventory_window_button(s_ptr<gui> mainSceneGUI) {
    mainSceneGUI->add_child_component(std::make_shared<gui_button>(
        0.85f, 0.9f, 0.05f, ConvertWidthToHeight(0.05f), "",
        [] { GetSingleton<gui_inventory_window>().toggle_visibility(); },
        "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground"));
  }
}