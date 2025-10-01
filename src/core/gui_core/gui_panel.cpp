/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_panel.hpp"
#include "core/rendering/images/image_renderer.hpp"

namespace forr {
  void gui_panel::RenderDerived() const {
    auto bounds{GetBounds()};
    GetSingleton<image_renderer>().DrawImage(m_backgroundImage, bounds.x, bounds.y,
                                 bounds.width, bounds.height);
  }
}
