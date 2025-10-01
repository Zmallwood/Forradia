/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "add_main_scene_gui_components.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_fps_panel.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "core/gui_core/windows/gui_window.hpp"
#include "sub/add_main_scene_gui_buttons.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_inventory_window.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_player_body_window.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_player_status_panel.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_system_menu.hpp"

namespace forr {
  void add_main_scene_gui_components(std::shared_ptr<gui> mainSceneGUI) {
    mainSceneGUI->add_child_component(
        std::make_shared<gui_player_status_panel>());
    mainSceneGUI->add_child_component(GetSingletonPtr<gui_text_console>());
    add_main_scene_gui_buttons(mainSceneGUI);
    mainSceneGUI->add_child_component(GetSingletonPtr<gui_system_menu>());
    mainSceneGUI->add_child_component(GetSingletonPtr<gui_inventory_window>());
    mainSceneGUI->add_child_component(
        GetSingletonPtr<gui_player_body_window>());
    mainSceneGUI->add_child_component(std::make_shared<gui_fps_panel>());
  }
}