/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIFPSPanel.hpp"
#include "GUILabel.hpp"
#include "Core/FPSCounter/FPSCounter.hpp"

namespace Forradia
{
    void GUIFPSPanel::Initialize()
    {
        m_fpsTextPanel = std::make_shared<GUILabel>(0.01f, 0.01f, 0.1f, 0.05f);

        AddChildComponent(m_fpsTextPanel);
    }

    void GUIFPSPanel::UpdateDerived()
    {
        GUIMovablePanel::UpdateDerived();

        auto fps{_<FPSCounter>().GetFPS()};

        m_fpsTextPanel->SetText(fmt::format("FPS: {}", fps));
    }
}