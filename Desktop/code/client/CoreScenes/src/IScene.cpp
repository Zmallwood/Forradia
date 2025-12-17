/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "IScene.hpp"
#include "GUI.hpp"

namespace Forradia {
auto IScene::Initialize() -> void {
  m_gui = std::make_shared<GUI>();

  this->InitializeDerived();
}

auto IScene::OnEnter() -> void {
  this->OnEnterDerived();
}

auto IScene::Update() -> void {
  m_gui->Update();

  this->UpdateDerived();
}

auto IScene::Render() const -> void {
  this->RenderDerived();

  m_gui->Render();
}
}
