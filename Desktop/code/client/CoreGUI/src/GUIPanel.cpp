/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIPanel.hpp"
#include "Image2DRenderer.hpp"

namespace Forradia {
auto GUIPanel::RenderDerived() const -> void {
  auto bounds{this->GetBounds()};
  _<Image2DRenderer>().DrawImageByName(k_renderIDBackground, m_backgroundImage, bounds.x, bounds.y,
                                       bounds.width, bounds.height, true);
}
}
