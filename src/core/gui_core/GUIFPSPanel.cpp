/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIFPSPanel.hpp"
#include "core/fps_counter/FPSCounter.hpp"
#include "GUILabel.hpp"

namespace Forradia {
  void GUIFPSPanel::Initialize() {
    m_fpsTextPanel = std::make_shared<GUILabel>(0.01f, 0.01f, 0.1f, 0.05f);

    AddChildComponent(m_fpsTextPanel);
  }

  void GUIFPSPanel::UpdateDerived() {
    GUIMovablePanel::UpdateDerived();

    auto fps{GetSingleton<FPSCounter>().GetFPS()};

    m_fpsTextPanel->SetText(fmt::format("FPS: {}", fps));
  }
}