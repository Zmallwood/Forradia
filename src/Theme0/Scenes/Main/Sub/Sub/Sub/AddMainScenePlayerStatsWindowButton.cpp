/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainScenePlayerStatsWindowButton.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIButton.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIPlayerStatsWindow.hpp"

namespace Forradia
{
    void AddMainScenePlayerStatsWindowButton(SharedPtr<GUI> mainSceneGUI)
    {
        mainSceneGUI->AddChildComponent(
            std::make_shared<GUIButton>(
                0.78f,
                0.9f,
                0.05f,
                ConvertWidthToHeight(0.05f),
                "",
                []
                {
                    _<GUIPlayerStatsWindow>().ToggleVisibility();
                },
                "GUIButtonStatsBackground",
                "GUIButtonStatsHoveredBackground"));
    }
}