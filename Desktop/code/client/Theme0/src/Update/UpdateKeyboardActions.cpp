//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "UpdateKeyboardActions.hpp"

#include "Keyboard/KeyboardInput.hpp"

#include "GUISystemMenu.hpp"

#include "GUIPlayerBodyWindow.hpp"

#include "GUIInventoryWindow.hpp"

#include "GUIChatBox.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void UpdateKeyboardActions()
    {
        if (_<KeyboardInput>().KeyIsPressedPickResult(SDLK_ESCAPE))
        {
            _<GUISystemMenu>().ToggleVisibility();
        }
        else if (_<KeyboardInput>().KeyIsPressedPickResult(SDLK_c))
        {
            _<GUIPlayerBodyWindow>().ToggleVisibility();
        }
        else if (_<KeyboardInput>().KeyIsPressedPickResult(SDLK_b))
        {
            _<GUIInventoryWindow>().ToggleVisibility();
        }
        else if (_<KeyboardInput>().KeyIsPressedPickResult(SDLK_RETURN))
        {
            if (_<GUIChatBox>().GetInputActive())
            {
                _<GUIChatBox>().SubmitInput();
            }
            else
            {
                _<GUIChatBox>().EnableInput();
            }
        }
    }
}