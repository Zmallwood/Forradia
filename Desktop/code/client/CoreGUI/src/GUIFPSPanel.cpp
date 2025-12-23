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
    auto GUIFPSPanel::initialize() -> void
    {
        m_fpsTextLabel =
            std::make_shared<GUILabel>("GUILabelFPSPanel", k_labelBounds.x, k_labelBounds.y,
                                       k_labelBounds.width, k_labelBounds.height);
        this->addChildComponent(dynamic_pointer_cast<GUIComponent, GUILabel>(m_fpsTextLabel));
    }

    auto GUIFPSPanel::updateDerived() -> void
    {
        GUIMovablePanel::updateDerived();

        auto fps{FPSCounter::instance().getFPS()};
        m_fpsTextLabel->setText(fmt::format("FPS: {}", fps));
    }
}
