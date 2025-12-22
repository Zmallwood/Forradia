/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIFPSPanel.hpp"
#include "FPSCounter.hpp"
#include "GUILabel.hpp"
#include <fmt/format.h>

namespace Forradia
{
    auto GUIFPSPanel::Initialize() -> void
    {
        m_fpsTextLabel =
            std::make_shared<GUILabel>("GUILabelFPSPanel", k_labelBounds.x, k_labelBounds.y,
                                       k_labelBounds.width, k_labelBounds.height);
        this->AddChildComponent(dynamic_pointer_cast<GUIComponent, GUILabel>(m_fpsTextLabel));
    }

    auto GUIFPSPanel::UpdateDerived() -> void
    {
        GUIMovablePanel::UpdateDerived();

        auto fps{FPSCounter::Instance().GetFPS()};
        m_fpsTextLabel->SetText(fmt::format("FPS: {}", fps));
    }
}
