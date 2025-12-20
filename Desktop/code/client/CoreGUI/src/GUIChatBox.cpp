/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIChatBox.hpp"
#include "Color2DRenderer.hpp"
#include "Coloring/Palette.hpp"
#include "Engine.hpp"
#include "Image2DRenderer.hpp"
#include "Keyboard/KeyboardInput.hpp"
#include "Singleton.hpp"
#include "TextRenderer.hpp"
#include <fmt/format.h>

namespace Forradia {
    auto GUIChatBox::Initialize() -> void {
        auto maxNumLines{this->GetMaxNumLines()};

        for (auto i = 0; i < maxNumLines; i++)
            m_renderIDsTextLines.push_back(Hash(fmt::format("RenderIDTextLine{}", i)));
    }

    auto GUIChatBox::GetMaxNumLines() const -> int {
        auto bounds{dynamic_cast<const GUIComponent *>(this)->GetBounds()};
        return static_cast<int>(bounds.height / k_lineHeight - 1);
    }

    auto GUIChatBox::UpdateDerived() -> void {
        dynamic_cast<GUIComponent *>(this)->GUIPanel::UpdateDerived();

        m_input = _<KeyboardInput>().GetTextInput();
    }

    auto GUIChatBox::RenderDerived() const -> void {
        dynamic_cast<const GUIPanel *>(this)->GUIPanel::RenderDerived();

        auto bounds{dynamic_cast<const GUIComponent *>(this)->GetBounds()};
        auto maxNumLines{this->GetMaxNumLines()};
        auto yPos{bounds.y + k_margin};

        // Loop through the text lines.
        for (auto i = 0; i < maxNumLines; i++) {
            auto index{m_lines.size() - maxNumLines + i};

            if (index < 0 || index >= m_lines.size())
                continue;

            auto textLine = m_lines.at(index);

            _<TextRenderer>().DrawString(m_renderIDsTextLines.at(i), textLine, bounds.x + k_margin,
                                         yPos, FontSizes::_20, false, true);

            yPos += k_lineHeight;
        }

        auto separatorX{bounds.x + k_margin};
        auto separatorY{bounds.y + bounds.height - k_lineHeight};
        auto separatorWidth{bounds.width - 2 * k_margin};
        auto sepratorHeight{k_separatorHeight};

        _<Color2DRenderer>().DrawLine(k_renderIDSeparator, Palette::GetColor<Hash("Black")>(),
                                      separatorX, separatorY, separatorX + separatorWidth,
                                      separatorY, sepratorHeight, true);

        if (m_inputActive) {
            // TODO: Calculate the cursor x-coordinate based on the text input.

            auto cursorX{bounds.x};
            auto cursorY{bounds.y + bounds.height - k_lineHeight};
            auto cursorWidth{k_cursorWidth};
            auto cursorHeight{k_lineHeight};

            _<Image2DRenderer>().DrawImageByName(k_renderIDInputCursor, "GUIInputCursor", cursorX,
                                                 cursorY, cursorWidth, cursorHeight);

            _<TextRenderer>().DrawString(k_renderIDInputText, m_input, cursorX, cursorY,
                                         FontSizes::_20, false, true);
        }
    }

    auto GUIChatBox::Print(std::string_view text) -> void {
        m_lines.emplace_back(text.data());
    }

    auto GUIChatBox::EnableInput() -> void {
        _<KeyboardInput>().StartTextInput();

        m_inputActive = true;
    }

    auto GUIChatBox::SubmitInput() -> void {
        // TODO: Act on the typed input.

        if (m_input == "/quit")
            _<Engine>().Stop();

        _<KeyboardInput>().StopTextInput();

        m_inputActive = false;
        m_input = "";
    }
}
