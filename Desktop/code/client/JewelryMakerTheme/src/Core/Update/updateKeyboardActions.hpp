/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <SDL2/SDL.h>

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Updates the keyboard actions.
     */
    auto updateKeyboardActions(SDL_Keycode key) -> void;
}
