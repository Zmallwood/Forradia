/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Core/GUICore/GUIWindow.hpp"

namespace Forradia
{
    class GUIPlayerStatsWindow : public GUIWindow
    {
    public:
        GUIPlayerStatsWindow()
            : GUIWindow(0.2f, 0.3f, 0.2f, 0.4f, "Player stats")
        {
        }

    protected:
        void RenderDerived() const override;
    };
}