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
        // Initialize the GUI.

        m_gui = std::make_shared<GUI>();

        // Call the derived initialize function.

        m_initializeDerived();
    }

    void IScene::OnEnter() {
        // Call the derived on enter function.

        m_onEnterDerived();
    }

    void IScene::Update() {
        // Update the GUI.

        m_gui->Update();

        // Call the derived update function.

        m_updateDerived();
    }

    void IScene::Render() const {
        // Call the derived render function.

        m_renderDerived();

        // Render the GUI.

        m_gui->Render();
    }
}