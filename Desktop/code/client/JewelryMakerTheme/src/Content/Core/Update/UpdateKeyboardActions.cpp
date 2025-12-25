/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "UpdateKeyboardActions.hpp"
    #include "Content/CustomGUI/GUIInventoryWindow.hpp"
    #include "Content/CustomGUI/GUISystemMenu.hpp" 
    #include "ForradiaEngine/GUICore/GUIChatBox.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
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
