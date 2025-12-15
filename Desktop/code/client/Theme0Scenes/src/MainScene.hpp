//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "IScene.hpp"

namespace Forradia::Theme0
{
    class MainScene : public IScene
    {
      public:
        MainScene();

      protected:
        virtual void InitializeDerived();

        virtual void OnEnterDerived();

        virtual void UpdateDerived();

        virtual void RenderDerived();
    };
}