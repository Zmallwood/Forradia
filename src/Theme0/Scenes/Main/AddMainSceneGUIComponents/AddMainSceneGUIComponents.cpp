/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainSceneGUIComponents.hpp"
#include "Sub/AddMainSceneGUIButtons.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUITextConsole.hpp"
#include "Core/GUICore/GUIWindow.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIPlayerStatusPanel.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUISystemMenu.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIPlayerStatsWindow.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIInventoryWindow.hpp"

namespace Forradia
{
    void AddMainSceneGUIComponents(std::shared_ptr<GUI> mainSceneGUI)
    {
        mainSceneGUI->AddChildComponent(
            std::make_shared<GUIPlayerStatusPanel>());

        mainSceneGUI->AddChildComponent(
            std::make_shared<GUITextConsole>());

        AddMainSceneGUIButtons(mainSceneGUI);

        mainSceneGUI->AddChildComponent(__<GUISystemMenu>());

        mainSceneGUI->AddChildComponent(__<GUIInventoryWindow>());

        mainSceneGUI->AddChildComponent(__<GUIPlayerStatsWindow>());
    }
}