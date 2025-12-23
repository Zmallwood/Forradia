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
    auto updateKeyboardActions(SDL_Keycode key) -> void
    {
        if (key == SDLK_ESCAPE)
        {
            GUISystemMenu::instance().toggleVisibility();
        }
        else if (key == SDLK_b)
        {
            GUIInventoryWindow::instance().toggleVisibility();
        }
        else if (key == SDLK_RETURN)
        {
            if (GUIChatBox::instance().getInputActive())
            {
                GUIChatBox::instance().submitInput();
            }
            else
            {
                GUIChatBox::instance().enableInput();
            }
        }
    }
}
