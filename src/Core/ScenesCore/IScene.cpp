/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "IScene.hpp"
#include "Core/GUICore/GUI.hpp"

namespace Forradia
{
    IScene::IScene()
        : m_gui(std::make_shared<GUI>())
    {
    }

    void IScene::Update()
    {
        UpdateDerived();
    }

    void IScene::Render() const
    {
        RenderDerived();
    }
}
