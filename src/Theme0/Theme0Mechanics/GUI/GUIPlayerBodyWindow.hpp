/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Core/GUICore/GUIWindow.hpp"

namespace Forradia
{
    class GUIPlayerBodyWindow : public GUIWindow
    {
    public:
        GUIPlayerBodyWindow()
            : GUIWindow(0.2f, 0.2f, 0.2f, 0.5f, "Player body") {}

    protected:
        void RenderDerived() const override;
    };
}