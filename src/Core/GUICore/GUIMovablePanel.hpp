/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    class GUIMovablePanel : public GUIPanel
    {
    public:
        GUIMovablePanel(float x,
                        float y,
                        float width,
                        float height)
            : GUIPanel(x, y, width, height)
        {
        }
    };
}
