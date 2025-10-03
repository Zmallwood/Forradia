/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "main_scene.hpp"
#include "core/gui/gui_text_console.hpp"
#include "sub/add_main_scene_gui_components.hpp"
#include "theme_0/mechanics/creatures_update/update_creature_movement.hpp"
#include "theme_0/mechanics/keyboard_bindings/update_keyboard_binding_actions.hpp"
#include "theme_0/mechanics/npcs_update/update_npcs.hpp"
#include "theme_0/mechanics/player_movement/update_keyboard_movement.hpp"
#include "theme_0/mechanics/player_movement/update_mouse_movement.hpp"
#include "theme_0/mechanics/world_interaction/tile_hovering.hpp"
#include "theme_0/mechanics/world_view/world_view.hpp"

namespace forr {
  void main_scene::initialize_derived() {
    add_main_scene_gui_components(get_gui());
  }

  void main_scene::on_enter_derived() {
    get_ston<gui_text_console>().print("You have entered the world.");
  }

  void main_scene::update_derived() {
    update_npcs();
    update_creature_movement();
    update_mouse_movement();
    update_keyboard_movement();
    get_ston<tile_hovering>().update();
    update_keyboard_binding_actions();
  }

  void main_scene::render_derived() const { get_ston<world_view>().render(); }
}
