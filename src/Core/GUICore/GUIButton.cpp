/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIButton.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"
#include "Core/Cursor/Cursor.hpp"

namespace Forradia
{
    GUIButton::GUIButton(float x,
                         float y,
                         float width,
                         float height,
                         StringView text,
                         Function<void()> action,
                         StringView backgroundImage,
                         StringView hoveredBackgroundImage)
        : GUIPanel(x, y, width, height),
          m_text(text),
          m_action(action),
          m_backgroundImage(backgroundImage),
          m_hoveredBackgroundImage(hoveredBackgroundImage)
    {
    }

    void GUIButton::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        auto mousePosition{GetNormalizedMousePosition()};

        auto isHovered{GetBounds().Contains(mousePosition)};

        if (isHovered)
        {
            SetBackgroundImage(m_hoveredBackgroundImage);

            _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

            if (_<MouseInput>().GetLeftMouseButtonRef().IsPressedPickResult())
            {
                _<MouseInput>().GetLeftMouseButtonRef().Reset();

                m_action();
            }
        }
        else
        {
            SetBackgroundImage(m_backgroundImage);
        }
    }

    void GUIButton::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{GetBounds()};

        _<TextRenderer>().DrawString(
            m_text,
            bounds.x + bounds.width / 2,
            bounds.y + bounds.height / 2,
            FontSizes::_20,
            true);
    }
}
