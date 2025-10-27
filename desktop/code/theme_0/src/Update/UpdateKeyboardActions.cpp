//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TileHovering.hpp"

#include "Input/Keyboard/KeyboardInput.hpp"

#include "CustomGUI/GUISystemMenu.hpp"

#include "CustomGUI/GUIPlayerBodyWindow.hpp"

#include "CustomGUI/GUIInventoryWindow.hpp"

namespace Forradia
{
    namespace Theme0
    {
        namespace GameplayCore
        {
            void UpdateKeyboardActions()
            {
                if (_<KeyboardInput>()
                        .KeyIsPressedPickResult(
                            SDLK_ESCAPE))
                {
                    _<GUISystemMenu>().ToggleVisibility();
                }
                else if (_<KeyboardInput>()
                             .KeyIsPressedPickResult(
                                 SDLK_c))
                {
                    _<GUIPlayerBodyWindow>()
                        .ToggleVisibility();
                }
                else if (_<KeyboardInput>()
                             .KeyIsPressedPickResult(
                                 SDLK_b))
                {
                    _<GUIInventoryWindow>()
                        .ToggleVisibility();
                }
            }
        }
    }
}