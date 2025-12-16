/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIFPSPanel.hpp"
#include "FPSCounter.hpp"
#include "GUILabel.hpp"

namespace Forradia {
void GUIFPSPanel::Initialize() {
  m_fpsTextPanel = std::make_shared<GUILabel>("GUILabelFPSPanel", 0.01f, 0.01f, 0.1f, 0.05f);
  this->AddChildComponent(m_fpsTextPanel);
}

void GUIFPSPanel::UpdateDerived() {
  GUIMovablePanel::UpdateDerived();

  auto fps{_<FPSCounter>().GetFPS()};
  m_fpsTextPanel->SetText(fmt::format("FPS: {}", fps));
}
}