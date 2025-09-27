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
        using GUIWindow::GUIWindow;

    protected:
        void RenderDerived() const override;
    };
}