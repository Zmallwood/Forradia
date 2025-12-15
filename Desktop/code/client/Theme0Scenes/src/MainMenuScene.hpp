//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "IScene.hpp"

namespace Forradia::Theme0
{
    class MainMenuScene : public IScene
    {
      public:
        MainMenuScene();

      protected:
        virtual void InitializeDerived();

        virtual void RenderDerived();
    };
}