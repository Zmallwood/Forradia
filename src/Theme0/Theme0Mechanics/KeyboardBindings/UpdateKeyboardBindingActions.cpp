/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "UpdateKeyboardBindingActions.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"

namespace Forradia
{
    void UpdateKeyboardBindingActions()
    {
        if (_<KeyboardInput>().KeyIsPressedPickResult(SDLK_1))
        {
            std::cout << _<World>().GetCurrentWorldArea()->GetTile(_<Player>().GetPosition())->GetElevation() << "\n";
        }
    }
}