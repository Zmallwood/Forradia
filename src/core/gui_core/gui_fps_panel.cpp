/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_fps_panel.hpp"
#include "core/fps_counter/fps_counter.hpp"
#include "gui_label.hpp"

namespace forr {
  void gui_fps_panel::Initialize() {
    m_fpsTextPanel = std::make_shared<gui_label>(0.01f, 0.01f, 0.1f, 0.05f);
    AddChildComponent(m_fpsTextPanel);
  }

  void gui_fps_panel::UpdateDerived() {
    gui_movable_panel::UpdateDerived();
    auto fps{GetSingleton<fps_counter>().GetFPS()};
    m_fpsTextPanel->SetText(fmt::format("FPS: {}", fps));
  }
}