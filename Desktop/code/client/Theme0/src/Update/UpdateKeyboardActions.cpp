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
#include "Player/PlayerCharacter.hpp"

namespace AAK
{
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
            else if (_<KeyboardInput>().KeyIsPressedPickResult(SDLK_TAB))
            {
                auto currentMode{_<PlayerCharacter>().GetPlayerMode()};

                switch (currentMode)
                {
                case PlayerModes::Interaction:
                    _<PlayerCharacter>().SetPlayerMode(PlayerModes::Battle);

                    _<GUIChatBox>().Print("You are now in battle mode.");
                    break;
                case PlayerModes::Battle:
                    _<PlayerCharacter>().SetPlayerMode(PlayerModes::Interaction);

                    _<GUIChatBox>().Print("You are now in interaction mode.");
                    break;
                }
            }
        }
    }
}