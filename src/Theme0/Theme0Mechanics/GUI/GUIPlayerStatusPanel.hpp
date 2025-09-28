/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Core/GUICore/GUIPanel.hpp"

namespace Forradia
{
    class GUIPlayerStatusPanel : public GUIPanel
    {
    public:
        GUIPlayerStatusPanel()
            : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
        {
        }

    protected:
        virtual void RenderDerived() const override;
    };
}
