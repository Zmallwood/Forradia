/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia
{
    class GUIWindow : public GUIMovablePanel
    {
    public:
        GUIWindow(float x,
                  float y,
                  float width,
                  float height)
            : GUIMovablePanel(x, y, width, height)
        {
            Initialize();
        }

    private:
        void Initialize();
    };
}
