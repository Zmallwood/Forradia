//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "GUILabel.hpp"
#include "TextRenderer.hpp"

namespace Forradia
{
    void GUILabel::RenderDerived() const
    {
        // Get the bounds of this label.

        auto bounds{GetBounds()};

        auto x{bounds.x};

        auto y{bounds.y};

        // If the text should be centered, center the text.

        if (m_centerAlign)
        {
            bounds.x += bounds.width / 2;

            bounds.y += bounds.height / 2;
        }

        // Draw the text.

        _<TextRenderer>().DrawString(k_renderIDText, m_text, bounds.x, bounds.y, FontSizes::_20,
                                     m_centerAlign, true, m_color);
    }
}