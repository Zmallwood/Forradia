/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "updateKeyboardActions.hpp"
#include "CustomGUI/GUIInventoryWindow.hpp"
#include "CustomGUI/GUISystemMenu.hpp"
#include "CustomGUI/GUICraftingWindow.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto updateKeyboardActions(SDL_Keycode key) -> void
    {
        If(key == SDLK_ESCAPE)
        {
            GUISystemMenu::instance().toggleVisibility();
        }
        ElseIf(key == SDLK_b)
        {
            GUIInventoryWindow::instance().toggleVisibility();
        }
        ElseIf(key == SDLK_c)
        {
            GUICraftingWindow::instance().toggleVisibility();
        }
        ElseIf(key == SDLK_RETURN)
        {
            If(GUIChatBox::instance().getInputActive())
            {
                GUIChatBox::instance().submitInput();
            }
            Else
            {
                GUIChatBox::instance().enableInput();
            }
        }
    }
}
