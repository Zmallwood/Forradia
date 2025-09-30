/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIPanel.hpp"
#include "core/rendering/images/ImageRenderer.hpp"

namespace Forradia {
  void GUIPanel::RenderDerived() const {
    auto bounds{GetBounds()};

    GetSingleton<ImageRenderer>().DrawImage(m_backgroundImage, bounds.x, bounds.y,
                                 bounds.width, bounds.height);
  }
}
