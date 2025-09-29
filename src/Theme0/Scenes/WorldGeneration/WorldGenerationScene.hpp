/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Core/ScenesCore/IScene.hpp"

namespace Forradia
{
    class WorldGenerationScene : public IScene
    {
    protected:
        void OnEnterDerived() override;
    };
}
