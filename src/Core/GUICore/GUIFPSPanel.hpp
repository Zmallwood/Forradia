/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia
{
    class GUILabel;

    class GUIFPSPanel : public GUIMovablePanel
    {
    public:
        GUIFPSPanel()
            : GUIMovablePanel(0.92f, 0.02f, 0.07f, 0.04f)
        {
            Initialize();
        }

    protected:
        void UpdateDerived() override;

    private:
        void Initialize();

        SharedPtr<GUILabel> m_fpsTextPanel;
    };
}