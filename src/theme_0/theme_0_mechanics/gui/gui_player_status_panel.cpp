/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_player_status_panel.hpp"
#include "core/rendering/text/text_renderer.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"

namespace forr {
  void gui_player_status_panel::render_derived() const {
    gui_panel::render_derived();
    auto bounds{get_bounds()};
    get_singleton<text_renderer>().draw_string(
        get_singleton<player>().get_name(), bounds.x + 0.01f, bounds.y + 0.01f,
        font_sizes::_26);
  }
}