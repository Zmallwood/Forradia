/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Core/ScenesCore/IScene.hpp"

namespace Forradia
{
    class MainScene : public IScene
    {
    protected:
        void InitializeDerived() override;

        void UpdateDerived() override;

        void RenderDerived() const override;
    };
}
