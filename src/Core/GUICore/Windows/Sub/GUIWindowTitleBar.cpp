/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIWindowTitleBar.hpp"
#include "../GUIWindow.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"
#include "Core/Cursor/Cursor.hpp"

namespace Forradia
{
    void GUIWindowTitleBar::Update()
    {
        auto mousePosition{GetNormalizedMousePosition()};

        auto bounds{GetBounds()};

        if (bounds.Contains(mousePosition))
        {
            _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

            if (_<MouseInput>().GetLeftMouseButtonRef().GetHasBeenFiredPickResult())
            {
                m_parentWindow.SetIsBeingMoved(true);
            }
        }

        if (_<MouseInput>().GetLeftMouseButtonRef().GetHasBeenReleasedPickResult())
        {
            m_parentWindow.SetIsBeingMoved(false);
        }
    }

    void GUIWindowTitleBar::Render() const
    {
        auto parentWindowBounds{m_parentWindow.GetBounds()};

        _<ImageRenderer>().DrawImage("GUIWindowTitleBarBackground",
                                     parentWindowBounds.x,
                                     parentWindowBounds.y,
                                     parentWindowBounds.width,
                                     k_height);

        _<TextRenderer>().DrawString(k_windowTitleText,
                                     parentWindowBounds.x + 0.01f,
                                     parentWindowBounds.y + 0.01f,
                                     FontSizes::_20,
                                     false,
                                     Colors::yellow);
    }

    RectF GUIWindowTitleBar::GetBounds() const
    {
        RectF boundsResult;

        auto parentWindowBounds{m_parentWindow.GetBounds()};

        boundsResult.x = parentWindowBounds.x;
        boundsResult.y = parentWindowBounds.y;
        boundsResult.width = parentWindowBounds.width;
        boundsResult.height = k_height;

        return boundsResult;
    }
}