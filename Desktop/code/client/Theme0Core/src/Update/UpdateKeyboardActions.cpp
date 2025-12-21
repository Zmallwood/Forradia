/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateKeyboardActions.hpp"
#include "GUIChatBox.hpp"
#include "GUIInventoryWindow.hpp"
#include "GUIPlayerBodyWindow.hpp"
#include "GUISystemMenu.hpp"
#include "Player/Player.hpp"
#include "Tile.hpp"
#include "Update/TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
    auto UpdateKeyboardActions(SDL_Keycode key) -> void {
        if (key == SDLK_ESCAPE) {
            _<GUISystemMenu>().ToggleVisibility();
        } else if (key == SDLK_c) {
            _<GUIPlayerBodyWindow>().ToggleVisibility();
        } else if (key == SDLK_b) {
            _<GUIInventoryWindow>().ToggleVisibility();
        } else if (key == SDLK_RETURN) {
            if (_<GUIChatBox>().GetInputActive())
                _<GUIChatBox>().SubmitInput();
            else
                _<GUIChatBox>().EnableInput();
        } else if (key == SDLK_TAB) {
            // auto currentMode{_<Player>().GetPlayerMode()};

            // switch (currentMode) {
            // case PlayerModes::Interaction:
            //   _<Player>().SetPlayerMode(PlayerModes::Battle);
            //   _<GUIChatBox>().Print("You are now in battle mode.");
            //   break;
            // case PlayerModes::Battle:
            //   _<Player>().SetPlayerMode(PlayerModes::Interaction);
            //   _<GUIChatBox>().Print("You are now in interaction mode.");
            //   break;
            // }
        }
    }
}
