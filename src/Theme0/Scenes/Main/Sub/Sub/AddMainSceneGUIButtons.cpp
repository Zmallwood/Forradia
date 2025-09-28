/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainSceneGUIButtons.hpp"
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