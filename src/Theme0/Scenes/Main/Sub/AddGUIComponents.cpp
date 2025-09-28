/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddGUIComponents.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIButton.hpp"
#include "Core/GUICore/GUITextConsole.hpp"
#include "Core/GUICore/GUIWindow.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIPlayerStatusPanel.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUISystemMenu.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIPlayerStatsWindow.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIInventoryWindow.hpp"

namespace Forradia
{
    void AddGUIComponents(std::shared_ptr<GUI> mainSceneGUI)
    {
        mainSceneGUI->AddChildComponent(
            std::make_shared<GUIPlayerStatusPanel>());

        mainSceneGUI->AddChildComponent(
            std::make_shared<GUITextConsole>());

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

        mainSceneGUI->AddChildComponent(
            std::make_shared<GUIButton>(
                0.85f,
                0.9f,
                0.05f,
                ConvertWidthToHeight(0.05f),
                "",
                []
                {
                    _<GUIInventoryWindow>().ToggleVisibility();
                },
                "GUIButtonInventoryBackground",
                "GUIButtonInventoryHoveredBackground"));

        mainSceneGUI->AddChildComponent(
            std::make_shared<GUIButton>(
                0.92f,
                0.9f,
                0.05f,
                ConvertWidthToHeight(0.05f),
                "",
                []
                {
                    _<GUISystemMenu>().ToggleVisibility();
                },
                "GUIButtonSystemBackground",
                "GUIButtonSystemHoveredBackground"));

        mainSceneGUI->AddChildComponent(__<GUISystemMenu>());

        mainSceneGUI->AddChildComponent(__<GUIInventoryWindow>());

        mainSceneGUI->AddChildComponent(__<GUIPlayerStatsWindow>());
    }
}