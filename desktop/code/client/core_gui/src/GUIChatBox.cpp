//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIChatBox.hpp"

#include "FontSizes.hpp"

#include "TextRenderer.hpp"

#include "Image2DRenderer.hpp"

#include "Color2DRenderer.hpp"

namespace Forradia
{
    void GUIChatBox::Initialize()
    {
        // Initialize the render IDs for the text lines.

        auto maxNumLines{this->GetMaxNumLines()};

        for (auto i = 0; i < maxNumLines; i++)
        {
            // Create a render ID for the text line.

            m_renderIDsTextLines.push_back(Hash(fmt::format("RenderIDTextLine{}", i)));
        }
    }

    int GUIChatBox::GetMaxNumLines() const
    {
        // Get the bounds of the chat box.

        auto bounds{this->GetBounds()};

        // Calculate the maximum number of lines that can fit in the chat box.

        return CInt(bounds.height / k_lineHeight - 1);
    }

    void GUIChatBox::RenderDerived() const
    {
        // Call the base class specific render tasks as well as a standard procedure, even if they
        // do nothing in this case.

        GUIPanel::RenderDerived();

        // Get the bounds of the chat box.

        auto bounds{this->GetBounds()};

        // Get the maximum number of lines that can fit in the chat box.

        auto maxNumLines{this->GetMaxNumLines()};

        // Initialize the y-coordinate for the text lines.

        auto y{bounds.y + k_margin};

        // Loop through the text lines.

        for (auto i = 0; i < maxNumLines; i++)
        {
            // Compute the index of the text line.

            auto index{m_lines.size() - maxNumLines + i};

            // Index out of bounds check.

            if (index < 0 || index >= m_lines.size())
            {
                continue;
            }

            // Get the text line.

            auto textLine = m_lines.at(index);

            // Draw the text line.

            _<TextRenderer>().DrawString(m_renderIDsTextLines.at(i), textLine, bounds.x + k_margin,
                                         y, FontSizes::_20, false, true);

            // Update the y-coordinate for the next text line.

            y += k_lineHeight;
        }

        // Get separator bounds.

        auto separatorX{bounds.x + k_margin};

        auto separatorY{bounds.y + bounds.height - k_lineHeight};

        auto separatorWidth{bounds.width - 2 * k_margin};

        auto sepratorHeight{k_separatorHeight};

        // Draw the separator.

        _<Color2DRenderer>().DrawLine(k_renderIDSeparator, Palette::GetColor<Hash("Black")>(),
                                      separatorX, separatorY, separatorX + separatorWidth,
                                      separatorY, sepratorHeight);

        // If the input is active.

        if (m_inputActive)
        {
            // Get the cursor bounds.

            // TODO: Calculate the cursor x-coordinate based on the text input.

            auto cursorX{bounds.x};

            auto cursorY{bounds.y + bounds.height - k_lineHeight};

            auto cursorWidth{0.01f};

            auto cursorHeight{k_lineHeight};

            // Draw the cursor.

            _<Image2DRenderer>().DrawImageByName(k_renderIDInputCursor, "GUIInputCursor", cursorX,
                                                 cursorY, cursorWidth, cursorHeight);
        }
    }

    void GUIChatBox::Print(StringView text)
    {
        // Add the text to the lines.

        m_lines.push_back(text.data());
    }

    void GUIChatBox::EnableInput()
    {
        // Set the input active flag to true.

        m_inputActive = true;
    }

    void GUIChatBox::SubmitInput()
    {
        // TODO: Act on the typed input.

        // Reset the input state.
        
        m_inputActive = false;

        m_input = "";
    }
}