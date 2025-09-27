/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUILabel.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"

namespace Forradia
{
    GUILabel::GUILabel(float x,
                       float y,
                       float width,
                       float height,
                       std::string_view text)
        : GUIComponent(x, y, width, height),
          m_text(text)
    {
    }

    void GUILabel::RenderDerived() const
    {
        auto bounds{GetBounds()};

        _<TextRenderer>().DrawString(
            m_text,
            bounds.x + bounds.width / 2,
            bounds.y + bounds.height / 2,
            FontSizes::_20,
            true);
    }
}
