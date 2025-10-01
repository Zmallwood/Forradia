/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "i_scene.hpp"
#include "core/gui_core/gui.hpp"

namespace forr {
  void i_scene::Initialize() {
    m_gui = std::make_shared<gui>();
    InitializeDerived();
  }

  void i_scene::OnEnter() { OnEnterDerived(); }

  void i_scene::Update() {
    m_gui->Update();
    UpdateDerived();
  }

  void i_scene::Render() const {
    RenderDerived();
    m_gui->Render();
  }
}
