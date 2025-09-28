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
                  float height,
                  StringView windowTitle)
            : GUIMovablePanel(x, y, width, height),
              k_windowTitle(windowTitle)
        {
            Initialize();
        }

    protected:
        void RenderDerived() const override;

    private:
        void Initialize();

        const String k_windowTitle;
        const float k_titleBarHeight{0.04f};
    };
}
