/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUILabel.hpp"
#include "TextRenderer.hpp"

namespace Forradia
{
    auto GUILabel::RenderDerived() const -> void
    {
        auto bounds{dynamic_cast<const GUIComponent *>(this)->GetBounds()};

        // ReSharper disable once CppDFAConstantConditions
        if (m_centerAlign)
        {
            // ReSharper disable once CppDFAUnreachableCode
            bounds.x += bounds.width / 2;
            bounds.y += bounds.height / 2;
        }

        TextRenderer::Instance().DrawString(k_renderIDText, m_text, bounds.x, bounds.y,
                                            FontSizes::_20, m_centerAlign, true, m_color);
    }
}
