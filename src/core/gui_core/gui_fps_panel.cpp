/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_fps_panel.hpp"
#include "core/fps_counter/fps_counter.hpp"
#include "gui_label.hpp"

namespace forr {
  void gui_fps_panel::initialize() {
    m_fps_text_panel = std::make_shared<gui_label>(0.01f, 0.01f, 0.1f, 0.05f);
    add_child_component(m_fps_text_panel);
  }

  void gui_fps_panel::update_derived() {
    gui_movable_panel::update_derived();
    auto fps{get_singleton<fps_counter>().get_fps()};
    m_fps_text_panel->set_text(fmt::format("FPS: {}", fps));
  }
}