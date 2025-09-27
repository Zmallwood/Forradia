/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIWindow.hpp"

namespace Forradia
{
    GUIWindow::GUIWindow(float x,
                         float y,
                         float width,
                         float height)
        : GUIMovablePanel(x, y, width, height)
    {
        SetVisible(false);
    }
}
