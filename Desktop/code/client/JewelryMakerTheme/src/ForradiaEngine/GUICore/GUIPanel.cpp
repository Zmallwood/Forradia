/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIPanel.hpp"
#include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"

namespace ForradiaEngine
{
    auto GUIPanel::renderDerived() const -> void
    {
        auto bounds{this->getBounds()};

        Image2DRenderer::instance().drawImageByName(k_renderIDBackground, m_activeBackgroundImage,
                                                    bounds.x, bounds.y, bounds.width, bounds.height,
                                                    true);
    }
}
