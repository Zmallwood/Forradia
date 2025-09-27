/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "UpdateKeyboardBindingActions.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Theme0/Theme0Mechanics/GUI/GUISystemMenu.hpp"

namespace Forradia
{
    void UpdateKeyboardBindingActions()
    {
        if (_<KeyboardInput>().KeyIsPressedPickResult(SDLK_ESCAPE))
        {
            _<MainScene>().GetGUISystemMenu()->ToggleVisibility();
        }
    }
}