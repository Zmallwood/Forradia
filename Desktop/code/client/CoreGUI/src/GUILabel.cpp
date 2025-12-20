/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUILabel.hpp"
#include "Singleton.hpp"
#include "TextRenderer.hpp"

namespace Forradia {
    auto GUILabel::RenderDerived() const -> void {
        auto bounds{dynamic_cast<const GUIComponent *>(this)->GetBounds()};

        if (m_centerAlign) {
            bounds.x += bounds.width / 2;
            bounds.y += bounds.height / 2;
        }

        _<TextRenderer>().DrawString(k_renderIDText, m_text, bounds.x, bounds.y, FontSizes::_20,
                                     m_centerAlign, true, m_color);
    }
}
