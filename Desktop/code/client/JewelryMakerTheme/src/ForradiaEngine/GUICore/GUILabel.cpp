/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUILabel.hpp"
#include "ForradiaEngine/Rendering/Text/TextRenderer.hpp"

namespace ForradiaEngine
{
    auto GUILabel::renderDerived() const -> void
    {
        auto bounds{dynamic_cast<const GUIComponent *>(this)->getBounds()};

        if (m_centerAlign)
        {
            bounds.x += bounds.width / 2;
            bounds.y += bounds.height / 2;
        }

        TextRenderer::instance().drawString(k_renderIDText, m_text, bounds.x, bounds.y,
                                            FontSizes::_20, m_centerAlign, true, m_color);
    }
}
