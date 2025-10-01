/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "i_scene.hpp"
#include "core/gui_core/gui.hpp"

namespace forr {
  void IScene::Initialize() {
    m_gui = std::make_shared<GUI>();
    InitializeDerived();
  }

  void IScene::OnEnter() { OnEnterDerived(); }

  void IScene::Update() {
    m_gui->Update();
    UpdateDerived();
  }

  void IScene::Render() const {
    RenderDerived();
    m_gui->Render();
  }
}
