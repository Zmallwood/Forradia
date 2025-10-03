/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_player_status_panel.hpp"
#include "core/rend/text_renderer.hpp"
#include "theme_0/func/core_objs/player.hpp"

namespace forr {
  void gui_player_status_panel::render_derived() const {
    gui_panel::render_derived();
    auto b{get_bounds()};
    get_ston<text_renderer>().draw_str(get_ston<player>().get_name(),
                                          b.x + 0.01f, b.y + 0.01f,
                                          font_sizes::_26);
  }
}