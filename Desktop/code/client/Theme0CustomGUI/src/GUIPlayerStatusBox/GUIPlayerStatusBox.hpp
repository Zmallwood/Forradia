//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIPanel.hpp"

namespace Forradia::Theme0
{
    class GUIPlayerStatusBox : public GUIPanel
    {
      public:
        GUIPlayerStatusBox() : GUIPanel("GUIPlayerStatusBox", 0.0f, 0.0f, 0.2f, 0.14f)
        {
            this->Initialize();
        }

      protected:
        void Initialize();

        virtual void RenderDerived() const override;

      private:
        const int k_renderIDNameString{Hash("GUIPlayerStatusBoxName")};

        const int k_renderLevelString{Hash("GUIPlayerStatusBoxLevel")};

        const int k_renderHealthString{Hash("GUIPlayerStatusBoxHealth")};

        const int k_renderHealthValueString{Hash("GUIPlayerStatusBoxHealthValue")};
    };
}