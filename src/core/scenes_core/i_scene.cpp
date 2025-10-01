/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "i_scene.hpp"
#include "core/gui_core/gui.hpp"

namespace forr {
  void i_scene::initialize() {
    m_gui = std::make_shared<gui>();
    initialize_derived();
  }

  void i_scene::on_enter() { on_enter_derived(); }

  void i_scene::update() {
    m_gui->update();
    update_derived();
  }

  void i_scene::render() const {
    render_derived();
    m_gui->render();
  }
}
