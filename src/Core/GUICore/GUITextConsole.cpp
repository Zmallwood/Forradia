/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUITextConsole.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"

namespace Forradia
{
    void GUITextConsole::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{GetBounds()};

        auto y {bounds.y + k_margin};

        for (auto& textLine : m_textLines)
        {
            _<TextRenderer>().DrawString(textLine, bounds.x + k_margin, y);

            y += k_lineHeight;
        }

        auto separatorRect{RectF{bounds.x, bounds.y + bounds.height - k_lineHeight, bounds.width, k_separatorHeight}};

        _<ImageRenderer>().DrawImage("Black", separatorRect.x, separatorRect.y, separatorRect.width, separatorRect.height);
    }

    void GUITextConsole::Print(StringView text)
    {
        m_textLines.push_back(text.data());
    }
}