/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "main_scene.hpp"
#include "gui.hpp"
#include "theme_0/func/creas_update/update_crea_movem.hpp"
#include "theme_0/func/gui/gui_inventory_window.hpp"
#include "theme_0/func/gui/gui_player_body_window.hpp"
#include "theme_0/func/gui/gui_player_status_panel.hpp"
#include "theme_0/func/gui/gui_system_menu.hpp"
#include "theme_0/func/kb_bindings/update_kb_actions.hpp"
#include "theme_0/func/npcs_update/update_npcs.hpp"
#include "theme_0/func/player_movem/update_kb_movem.hpp"
#include "theme_0/func/player_movem/update_mouse_movem.hpp"
#include "theme_0/func/world_interact/tile_hovering.hpp"
#include "theme_0/func/world_view/world_view.hpp"

namespace forr {
  void main_scene::init_derived() {
    get_gui()->add_child_component(std::make_shared<gui_player_status_panel>());
    get_gui()->add_child_component(__<gui_text_console>());
    get_gui()->add_child_component(std::make_shared<gui_button>(
        0.78f, 0.9f, 0.05f, conv_w_to_h(0.05f), "",
        [] { _<gui_player_body_window>().toggle_visibility(); },
        "GUIButtonPlayerBodyBackground",
        "GUIButtonPlayerBodyHoveredBackground"));

    get_gui()->add_child_component(std::make_shared<gui_button>(
        0.85f, 0.9f, 0.05f, conv_w_to_h(0.05f), "",
        [] { _<gui_inventory_window>().toggle_visibility(); },
        "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground"));

    get_gui()->add_child_component(std::make_shared<gui_button>(
        0.92f, 0.9f, 0.05f, conv_w_to_h(0.05f), "",
        [] { _<gui_system_menu>().toggle_visibility(); },
        "GUIButtonSystemBackground", "GUIButtonSystemHoveredBackground"));
    get_gui()->add_child_component(__<gui_system_menu>());
    get_gui()->add_child_component(__<gui_inventory_window>());
    get_gui()->add_child_component(__<gui_player_body_window>());
    get_gui()->add_child_component(std::make_shared<gui_fps_panel>());
  }

  void main_scene::on_enter_derived() {
    _<gui_text_console>().print("You have entered the world.");
  }

  void main_scene::update_derived() {
    update_npcs();
    update_crea_movem();
    update_mouse_movem();
    update_kb_movem();
    _<tile_hovering>().update();
    update_kb_actions();
  }

  void main_scene::render_derived() const { _<world_view>().render(); }
}
