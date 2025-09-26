#pragma once

#include "Core/ScenesCore/IScene.hpp"

namespace Forradia
{
    class MainScene : public IScene
    {
    protected:
        void UpdateDerived() override;

        void RenderDerived() const override;
    };
}
