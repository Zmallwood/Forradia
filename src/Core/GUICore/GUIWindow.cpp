/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIWindow.hpp"
#include "Core/Rendering/Text/TextRenderer.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"

namespace Forradia
{
    void GUIWindow::Initialize()
    {
        SetVisible(false);
    }

    void GUIWindow::RenderDerived() const
    {
        GUIMovablePanel::RenderDerived();

        auto bounds{GetBounds()};

        _<ImageRenderer>().DrawImage("GUIWindowTitleBarBackground",
                                     bounds.x,
                                     bounds.y,
                                     bounds.width,
                                     k_titleBarHeight);

        _<TextRenderer>().DrawString(k_windowTitle,
                                     bounds.x + 0.01f,
                                     bounds.y + 0.01f,
                                     FontSizes::_20,
                                     false,
                                     Colors::yellow);
    }
}