/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MainScene.hpp"
#include "Theme0/Theme0Mechanics/WorldView/WorldView.hpp"
#include "Theme0/Theme0Mechanics/PlayerMovement/UpdateKeyboardMovement.hpp"
#include "Theme0/Theme0Mechanics/PlayerMovement/UpdateMouseMovement.hpp"
#include "Theme0/Theme0Mechanics/CreatureMovement/UpdateCreatureMovement.hpp"
#include "Theme0/Theme0Mechanics/KeyboardBindings/UpdateKeyboardBindingActions.hpp"
#include "Theme0/Theme0Mechanics/WorldInteraction/TileHovering.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIButton.hpp"
#include "Core/GUICore/GUITextConsole.hpp"
#include "Core/GUICore/GUIWindow.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIPlayerStatusPanel.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUISystemMenu.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUIPlayerStatsWindow.hpp"

namespace Forradia
{
    void MainScene::Initialize()
    {
        GetGUI()->AddChildComponent(
            std::make_shared<GUIPlayerStatusPanel>());

        GetGUI()->AddChildComponent(
            std::make_shared<GUITextConsole>());

        GetGUI()->AddChildComponent(
            std::make_shared<GUIButton>(
                0.78f,
                0.9f,
                0.05f,
                ConvertWidthToHeight(0.05f),
                "",
                [this]
                {
                    m_playerStatsWindow->ToggleVisibility();
                },
                "GUIButtonStatsBackground",
                "GUIButtonStatsHoveredBackground"));

        GetGUI()->AddChildComponent(
            std::make_shared<GUIButton>(
                0.85f,
                0.9f,
                0.05f,
                ConvertWidthToHeight(0.05f),
                "",
                [this]
                {
                    m_inventoryWindow->ToggleVisibility();
                },
                "GUIButtonInventoryBackground",
                "GUIButtonInventoryHoveredBackground"));

        GetGUI()->AddChildComponent(
            std::make_shared<GUIButton>(
                0.92f,
                0.9f,
                0.05f,
                ConvertWidthToHeight(0.05f),
                "",
                [this]
                {
                    m_guiSystemMenu->ToggleVisibility();
                },
                "GUIButtonSystemBackground",
                "GUIButtonSystemHoveredBackground"));

        m_guiSystemMenu = std::make_shared<GUISystemMenu>();

        GetGUI()->AddChildComponent(
            m_guiSystemMenu);

        m_inventoryWindow = std::make_shared<GUIWindow>(
            0.5f,
            0.3f,
            0.2f,
            0.4f);

        GetGUI()->AddChildComponent(
            m_inventoryWindow);

        m_playerStatsWindow = std::make_shared<GUIPlayerStatsWindow>(
            0.2f,
            0.3f,
            0.2f,
            0.4f);

        GetGUI()->AddChildComponent(
            m_playerStatsWindow);
    }

    void MainScene::UpdateDerived()
    {
        UpdateCreatureMovement();

        UpdateMouseMovement();

        UpdateKeyboardMovement();

        _<TileHovering>().Update();

        UpdateKeyboardBindingActions();
    }

    void MainScene::RenderDerived() const
    {
        _<WorldView>().Render();
    }
}
