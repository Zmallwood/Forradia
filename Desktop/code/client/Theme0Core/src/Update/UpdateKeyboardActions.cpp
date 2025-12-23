/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateKeyboardActions.hpp"
#include "GUIChatBox.hpp"
#include "GUIInventoryWindow.hpp"
#include "GUISystemMenu.hpp"

namespace Forradia::Theme0
{
    auto UpdateKeyboardActions(SDL_Keycode key) -> void
    {
        if (key == SDLK_ESCAPE)
        {
            GUISystemMenu::Instance().ToggleVisibility();
        }
        else if (key == SDLK_b)
        {
            GUIInventoryWindow::Instance().ToggleVisibility();
        }
        else if (key == SDLK_RETURN)
        {
            if (GUIChatBox::Instance().GetInputActive())
            {
                GUIChatBox::Instance().SubmitInput();
            }
            else
            {
                GUIChatBox::Instance().EnableInput();
            }
        }
    }
}
