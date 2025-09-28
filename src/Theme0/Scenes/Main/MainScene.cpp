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
#include "Sub/AddMainSceneGUIComponents.hpp"

namespace Forradia
{
    void MainScene::InitializeDerived()
    {
        AddMainSceneGUIComponents(GetGUI());
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
