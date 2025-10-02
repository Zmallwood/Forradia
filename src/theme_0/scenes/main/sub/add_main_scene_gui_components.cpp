/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "add_main_scene_gui_components.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_button.hpp"
#include "core/gui_core/gui_fps_panel.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "core/gui_core/windows/gui_window.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_inventory_window.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_player_body_window.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_player_status_panel.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_system_menu.hpp"

namespace forr {
  void add_main_scene_gui_components(std::shared_ptr<gui> main_scene_gui) {
    main_scene_gui->add_child_component(
        std::make_shared<gui_player_status_panel>());
    main_scene_gui->add_child_component(get_singleton_ptr<gui_text_console>());
    main_scene_gui->add_child_component(std::make_shared<gui_button>(
        0.78f, 0.9f, 0.05f, convert_width_to_height(0.05f), "",
        [] { get_singleton<gui_player_body_window>().toggle_visibility(); },
        "GUIButtonPlayerBodyBackground",
        "GUIButtonPlayerBodyHoveredBackground"));

    main_scene_gui->add_child_component(std::make_shared<gui_button>(
        0.85f, 0.9f, 0.05f, convert_width_to_height(0.05f), "",
        [] { get_singleton<gui_inventory_window>().toggle_visibility(); },
        "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground"));

    main_scene_gui->add_child_component(std::make_shared<gui_button>(
        0.92f, 0.9f, 0.05f, convert_width_to_height(0.05f), "",
        [] { get_singleton<gui_system_menu>().toggle_visibility(); },
        "GUIButtonSystemBackground", "GUIButtonSystemHoveredBackground"));
    main_scene_gui->add_child_component(get_singleton_ptr<gui_system_menu>());
    main_scene_gui->add_child_component(
        get_singleton_ptr<gui_inventory_window>());
    main_scene_gui->add_child_component(
        get_singleton_ptr<gui_player_body_window>());
    main_scene_gui->add_child_component(std::make_shared<gui_fps_panel>());
  }
}