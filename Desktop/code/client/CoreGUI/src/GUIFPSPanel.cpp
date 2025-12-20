/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIFPSPanel.hpp"
#include "FPSCounter.hpp"
#include "GUILabel.hpp"

namespace Forradia {
    auto GUIFPSPanel::Initialize() -> void {
        m_fpsTextPanel = std::make_shared<GUILabel>("GUILabelFPSPanel", 0.01F, 0.01F, 0.1F, 0.05F);
        this->AddChildComponent(m_fpsTextPanel);
    }

    auto GUIFPSPanel::UpdateDerived() -> void {
        GUIMovablePanel::UpdateDerived();

        auto fps{_<FPSCounter>().GetFPS()};
        m_fpsTextPanel->SetText(fmt::format("FPS: {}", fps));
    }
}
