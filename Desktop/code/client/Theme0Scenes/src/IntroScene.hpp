//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "IScene.hpp"

namespace Forradia {
    class GUIComponent;
}

namespace Forradia::Theme0 {
    class IntroScene : public IScene {
      public:
        IntroScene();

      protected:
        virtual void InitializeDerived();

        virtual void OnEnterDerived();

        virtual void UpdateDerived();

        virtual void RenderDerived();

      private:
        SharedPtr<GUIComponent> m_startText; ///< The text component for the start text.
    };
}