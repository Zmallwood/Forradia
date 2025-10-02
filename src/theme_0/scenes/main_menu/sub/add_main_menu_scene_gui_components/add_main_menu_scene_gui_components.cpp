/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "add_main_menu_scene_gui_components.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_panel.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "sub/add_main_menu_scene_gui_buttons.hpp"

namespace forr {
  void add_main_menu_scene_gui_components(s_ptr<gui> mainMenuSceneGUI) {
    mainMenuSceneGUI->add_child_component(
        std::make_shared<gui_panel>(0.4f, 0.32f, 0.2f, 0.2f));
    add_main_menu_scene_gui_buttons(mainMenuSceneGUI);
    mainMenuSceneGUI->add_child_component(
        get_singleton_ptr<gui_text_console>());
  }
}