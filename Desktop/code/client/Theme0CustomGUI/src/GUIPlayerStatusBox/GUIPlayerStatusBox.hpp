//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIPanel.hpp"

namespace AAK
{
    namespace Forradia
    {
        class GUILabel;
    }

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

            void UpdateDerived() override;

            void RenderDerived() const override;

          private:
            const int k_renderIDNameString{Hash("GUIPlayerStatusBoxName")};

            const int k_renderLevelString{Hash("GUIPlayerStatusBoxLevel")};

            const int k_renderWellBeingString{Hash("GUIPlayerStatusBoxWellBeing")};

            const int k_renderWellBeingValueString{Hash("GUIPlayerStatusBoxWellBeingValue")};

            SharedPtr<GUILabel> m_wellBeingValueTextLabel;
        };
    }
}