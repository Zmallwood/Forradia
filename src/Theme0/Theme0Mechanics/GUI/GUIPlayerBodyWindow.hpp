/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Core/GUICore/Windows/GUIWindow.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Sub/BodyPartTypes.hpp"

namespace Forradia
{
    class GUILabel;

    class GUIPlayerBodyWindow : public GUIWindow
    {
    public:
        GUIPlayerBodyWindow()
            : GUIWindow(0.2f, 0.2f, 0.2f, 0.5f, "Player body")
        {
            Initialize();
        }

    protected:
        void Initialize();

    private:
        void SelectBodyPart(BodyPartTypes bodyPartType);

        void UpdateBodyPartInformationLabels();

        BodyPartTypes m_selectedBodyPart{BodyPartTypes::None};
        SharedPtr<GUILabel> m_labelBodyPartName;
        SharedPtr<GUILabel> m_labelBodyPartStrength;
        SharedPtr<GUILabel> m_labelBodyPartEnergy;
        SharedPtr<GUILabel> m_labelBodyPartTemperature;
    };
}