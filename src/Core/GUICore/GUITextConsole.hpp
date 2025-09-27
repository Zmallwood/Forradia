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
        GUITextConsole();

    private:
        std::vector<std::string> m_textLines;
    };
}