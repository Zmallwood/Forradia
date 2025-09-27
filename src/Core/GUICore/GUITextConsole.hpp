/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    class GUITextConsole : public GUIPanel
    {
    public:
        GUITextConsole()
            : GUIPanel(0.0f, 0.8f, 0.4f, 0.2f, "GUIPanelSemiTransparentBackground")
        {
        }

    private:
        Vector<String> m_textLines;
    };
}