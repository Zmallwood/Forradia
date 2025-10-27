//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TileHovering.hpp"

#include "Input/Mouse/MouseInput.hpp"

#include "CustomGUI/GUIInteractionMenu.hpp"

#include "SDLDevice.hpp"

namespace Forradia
{
    namespace Theme0
    {
        namespace GameplayCore
        {
            void UpdateMouseActions()
            {
                if (_<MouseInput>()
                        .GetRightMouseButtonRef()
                        .HasBeenFiredPickResult())
                {
                    _<GUIInteractionMenu>().BuildMenu();

                    _<GUIInteractionMenu>().SetVisible(
                        true);

                    _<GUIInteractionMenu>().SetPosition(
                        GetNormallizedMousePosition(
                            _<SDLDevice>().GetWindow()));
                }
            }
        }
    }
}