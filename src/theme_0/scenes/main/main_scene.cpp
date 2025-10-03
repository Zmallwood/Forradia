/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "main_scene.hpp"
#include "core/gui.hpp"
#include "sub/add_main_scene_gui_components.hpp"
#include "theme_0/func/creas_update/update_crea_movem.hpp"
#include "theme_0/func/kb_bindings/update_kb_binding_actions.hpp"
#include "theme_0/func/npcs_update/update_npcs.hpp"
#include "theme_0/func/player_movem/update_kb_movem.hpp"
#include "theme_0/func/player_movem/update_mouse_movem.hpp"
#include "theme_0/func/world_interact/tile_hovering.hpp"
#include "theme_0/func/world_view/world_view.hpp"

namespace forr {
  void main_scene::init_derived() { add_main_scene_gui_components(get_gui()); }

  void main_scene::on_enter_derived() {
    get_ston<gui_text_console>().print("You have entered the world.");
  }

  void main_scene::update_derived() {
    update_npcs();
    update_crea_movem();
    update_mouse_movem();
    update_kb_binding_actions();
    get_ston<tile_hovering>().update();
    update_kb_binding_actions();
  }

  void main_scene::render_derived() const { get_ston<world_view>().render(); }
}
