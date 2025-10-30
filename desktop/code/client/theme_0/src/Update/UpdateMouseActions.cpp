//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TileHovering.hpp"

#include "Mouse/MouseInput.hpp"

#include "CustomGUI/GUIInteractionMenu/GUIInteractionMenu.hpp"

#include "SDLDevice.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void UpdateMouseActions()
    {
        if (_<MouseInput>()
                .GetRightMouseButtonRef()
                .HasBeenFiredPickResult())
        {
            _<GUIInteractionMenu>().BuildMenu();

            _<GUIInteractionMenu>().SetVisible(true);

            _<GUIInteractionMenu>().SetPosition(
                GetNormallizedMousePosition(
                    _<SDLDevice>().GetWindow()));
        }
    }
}