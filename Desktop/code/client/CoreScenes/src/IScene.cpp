//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "IScene.hpp"
#include "GUI.hpp"

namespace Forradia {
void IScene::Initialize() {
  m_gui = std::make_shared<GUI>();

  this->InitializeDerived();
}

void IScene::OnEnter() {
  this->OnEnterDerived();
}

void IScene::Update() {
  m_gui->Update();

  this->UpdateDerived();
}

void IScene::Render() const {
  this->RenderDerived();

  m_gui->Render();
}
}