//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIWindow.hpp"

namespace AAK
{
    namespace Forradia
    {
        class GUILabel;
    }

    namespace Forradia::Theme0
    {
        class GUIPlayerBodyWindow : public GUIWindow
        {
          public:
            GUIPlayerBodyWindow()
                : GUIWindow("GUIPlayerBodyWindow", 0.2f, 0.2f, 0.2f, 0.5f, "Player body")
            {
                this->Initialize();
            }

          protected:
            void Initialize();

          private:
            void SelectBodyPart(int type);

            void UpdateBodyPartInfoLabels();

            int m_selectedBodyPart{0};

            SharedPtr<GUILabel> m_labelBodyPartName;

            SharedPtr<GUILabel> m_labelBodyPartStrength;

            SharedPtr<GUILabel> m_labelBodyPartEnergy;

            SharedPtr<GUILabel> m_labelBodyPartTemperature;
        };
    }
}