//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIChatBox.hpp"

#include "Text/TextRenderer.hpp"

#include "Images2D/Image2DRenderer.hpp"

namespace Forradia
{
    void GUIChatBox::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{this->GetBounds()};

        auto maxNumLines{
            CInt(bounds.height / k_lineHeight - 1)};

        auto y{bounds.y + k_margin};

        for (auto i = 0; i < maxNumLines; i++)
        {
            auto index{m_lines.size() - maxNumLines + i};

            if (index < 0 || index >= m_lines.size())
            {
                continue;
            }

            auto textLine = m_lines.at(index);

            _<TextRenderer>().DrawString(
                textLine, bounds.x + k_margin, y);

            y += k_lineHeight;
        }

        auto separatorRect{
            RectF{bounds.x,
                  bounds.y + bounds.height - k_lineHeight,
                  bounds.width, k_separatorHeight}};

        _<Image2DRenderer>().DrawImageByName(
            "Black", separatorRect.x, separatorRect.y,
            separatorRect.width, separatorRect.height);

        if (m_inputActive)
        {
            auto cursorBounds{RectF{
                bounds.x,
                bounds.y + bounds.height - k_lineHeight,
                0.01f, k_lineHeight}};

            _<Image2DRenderer>().DrawImageByName(
                "GUIInputCursor", cursorBounds.x,
                cursorBounds.y, cursorBounds.width,
                cursorBounds.height);
        }
    }

    void GUIChatBox::Print(StringView text)
    {
        m_lines.push_back(text.data());
    }

    void GUIChatBox::EnableInput()
    {
        m_inputActive = true;
    }

    void GUIChatBox::SubmitInput()
    {
        m_inputActive = false;

        m_input = "";
    }
}