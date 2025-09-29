/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Core/GUICore/Windows/GUIWindow.hpp"

namespace Forradia
{
    class GUIInventoryWindow : public GUIWindow
    {
    public:
        GUIInventoryWindow()
            : GUIWindow(0.5f, 0.2f, 0.2f, 0.5f, "Inventory") {}

    protected:
        void RenderDerived() const override;
    };
}