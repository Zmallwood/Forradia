//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "IScene.hpp"

namespace Forradia
{
    void IScene::Initialize()
    {
        m_gui =
            std::make_shared<IScene::ScenesGUI::GUIRoot>();

        m_initializeDerived();
    }

    void IScene::OnEnter()
    {
        m_onEnterDerived();
    }

    void IScene::Update()
    {
        m_gui->Update();

        m_updateDerived();
    }

    void IScene::Render() const
    {
        m_renderDerived();

        m_gui->Render();
    }
}