/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MainScene.hpp"
#include "Theme0/Theme0Mechanics/WorldView/WorldView.hpp"
#include "Theme0/Theme0Mechanics/PlayerMovement/UpdateKeyboardMovement.hpp"
#include "Theme0/Theme0Mechanics/MobMovement/UpdateMobMovement.hpp"
#include "Theme0/Theme0Mechanics/KeyboardBindings/UpdateKeyboardBindingActions.hpp"
#include "Theme0/Theme0Mechanics/WorldInteraction/TileHovering.hpp"

namespace Forradia
{
    void MainScene::UpdateDerived()
    {
        UpdateMobMovement();

        UpdateKeyboardMovement();

        _<TileHovering>().Update();

        UpdateKeyboardBindingActions();
    }

    void MainScene::RenderDerived() const
    {
        _<WorldView>().Render();
    }
}
