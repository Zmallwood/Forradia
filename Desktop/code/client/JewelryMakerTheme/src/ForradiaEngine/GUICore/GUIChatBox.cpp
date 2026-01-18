/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIChatBox.hpp"
#include <fmt/format.h>
#include "ForradiaEngine/Rendering/Colors/Color2DRenderer.hpp"
#include "ForradiaEngine/Common/Matter/Coloring.hpp"
#include "ForradiaEngine/Engine.hpp"
#include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
#include "ForradiaEngine/Rendering/Text/TextRenderer.hpp"

namespace ForradiaEngine
{
    auto GUIChatBox::initialize() -> void
    {
        auto maxNumLines{this->getMaxNumLines()};

        for (auto i = 0; i < maxNumLines; i++)
        {
            m_renderIDsTextLines.push_back(hash(fmt::format("RenderIDTextLine{}", i)));
        }
    }

    auto GUIChatBox::getMaxNumLines() const -> int
    {
        auto bounds{dynamic_cast<const GUIComponent *>(this)->getBounds()};

        return static_cast<int>(bounds.height / k_lineHeight - 1);
    }

    auto GUIChatBox::updateDerived() -> void
    {
        dynamic_cast<GUIComponent *>(this)->GUIComponent::updateDerived();
    }

    auto GUIChatBox::renderDerived() const -> void
    {
        dynamic_cast<const GUIPanel *>(this)->GUIPanel::renderDerived();

        auto bounds{dynamic_cast<const GUIComponent *>(this)->getBounds()};
        auto maxNumLines{this->getMaxNumLines()};
        auto yPos{bounds.y + k_margin};

        // Loop through the text lines.
        for (auto i = 0; i < maxNumLines; i++)
        {
            auto index{m_lines.size() - maxNumLines + i};

            If(index < 0 || index >= m_lines.size())
            {
                continue;
            }

            auto textLine = m_lines.at(index);

            TextRenderer::instance().drawString(m_renderIDsTextLines.at(i), textLine,
                                                bounds.x + k_margin, yPos, FontSizes::_20, false,
                                                true);

            yPos += k_lineHeight;
        }

        auto separatorX{bounds.x + k_margin};
        auto separatorY{bounds.y + bounds.height - k_lineHeight};
        auto separatorWidth{bounds.width - 2 * k_margin};
        auto separatorHeight{k_separatorHeight};

        Color2DRenderer::instance().drawLine(
            k_renderIDSeparator, Palette::getColor<hash("Black")>(), separatorX, separatorY,
            separatorX + separatorWidth, separatorY, separatorHeight, true);

        If(m_inputActive)
        {
            // TODO: Calculate the cursor x-coordinate based on the text input.

            auto cursorX{bounds.x};
            auto cursorY{bounds.y + bounds.height - k_lineHeight};
            auto cursorWidth{k_cursorWidth};
            auto cursorHeight{k_lineHeight};

            Image2DRenderer::instance().drawImageByName(k_renderIDInputCursor, "GUIInputCursor",
                                                        cursorX, cursorY, cursorWidth,
                                                        cursorHeight);

            TextRenderer::instance().drawString(k_renderIDInputText, m_input, cursorX, cursorY,
                                                FontSizes::_20, false, true);
        }
    }

    auto GUIChatBox::print(std::string_view text) -> void
    {
        m_lines.emplace_back(text.data());
    }

    auto GUIChatBox::addTextInput(std::string_view text) -> void
    {
        m_input += text;
    }

    auto GUIChatBox::enableInput() -> void
    {
        SDL_StartTextInput();

        m_inputActive = true;
    }

    auto GUIChatBox::submitInput() -> void
    {
        // TODO: Act on the typed input.

        If(m_input == "/quit")
        {
            Engine::instance().stop();
        }

        SDL_StopTextInput();

        m_inputActive = false;
        m_input = "";
    }
}
