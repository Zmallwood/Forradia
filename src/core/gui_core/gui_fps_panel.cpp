/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_fps_panel.hpp"
#include "core/fps_counter/fps_counter.hpp"
#include "gui_label.hpp"

namespace forr {
  void gui_fps_panel::initialize() {
    m_fpsTextPanel = std::make_shared<gui_label>(0.01f, 0.01f, 0.1f, 0.05f);
    add_child_component(m_fpsTextPanel);
  }

  void gui_fps_panel::update_derived() {
    gui_movable_panel::update_derived();
    auto fps{GetSingleton<fps_counter>().get_fps()};
    m_fpsTextPanel->set_text(fmt::format("FPS: {}", fps));
  }
}