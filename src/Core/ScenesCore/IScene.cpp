/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "IScene.hpp"

namespace Forradia
{
    IScene::IScene()
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
