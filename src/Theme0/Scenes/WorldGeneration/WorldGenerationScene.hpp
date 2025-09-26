#pragma once

#include "Core/ScenesCore/IScene.hpp"

namespace Forradia
{
    class WorldGenerationScene : public IScene
    {
    protected:
        void OnEnter() override;
    };
}
