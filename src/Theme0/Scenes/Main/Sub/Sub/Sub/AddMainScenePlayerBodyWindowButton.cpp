/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainScenePlayerBodyWindowButton.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIButton.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIPlayerBodyWindow.hpp"

namespace Forradia
{
    void AddMainScenePlayerBodyWindowButton(SharedPtr<GUI> mainSceneGUI)
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
                    _<GUIPlayerBodyWindow>().ToggleVisibility();
                },
                "GUIButtonPlayerBodyBackground",
                "GUIButtonPlayerBodyHoveredBackground"));
    }
}