/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_panel.hpp"
#include "core/rend/images/image_renderer.hpp"

namespace forr {
  void gui_panel::render_derived() const {
    auto b{get_bounds()};
    get_singleton<image_renderer>().draw_image(m_bg_img, b.x, b.y,
                                               b.w, b.h);
  }
}
