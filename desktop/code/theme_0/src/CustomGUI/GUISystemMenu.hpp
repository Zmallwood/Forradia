//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUICore/GUIComponent.hpp"

namespace Forradia
{
    namespace Theme0
    {
        class GUISystemMenu : public GUIComponent
        {
          public:
            GUISystemMenu()
                : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
            {
                Initialize();
            }

          protected:
            void Initialize();

            virtual void UpdateDerived() override;

            virtual void RenderDerived() const override;
        };
    }
}