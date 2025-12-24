/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIPanel.hpp"
#include "Rendering/Images/Image2DRenderer.hpp"

namespace Forradia
{
    auto GUIPanel::renderDerived() const -> void
    {
        auto bounds{this->getBounds()};

        Image2DRenderer::instance().drawImageByName(k_renderIDBackground, m_backgroundImage,
                                                    bounds.x, bounds.y, bounds.width, bounds.height,
                                                    true);
    }
}
