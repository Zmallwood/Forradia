/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainSceneGUIButtons.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIButton.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUISystemMenu.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIPlayerStatsWindow.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIInventoryWindow.hpp"
#include "Sub/AddMainScenePlayerStatsWindowButton.hpp"
#include "Sub/AddMainSceneInventoryWindowButton.hpp"
#include "Sub/AddMainSceneSystemWindowButton.hpp"

namespace Forradia
{
    void AddMainSceneGUIButtons(SharedPtr<GUI> mainSceneGUI)
    {
        AddMainScenePlayerStatsWindowButton(mainSceneGUI);

        AddMainSceneInventoryWindowButton(mainSceneGUI);

        AddMainSceneSystemWindowButton(mainSceneGUI);
    }
}