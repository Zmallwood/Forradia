/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <SDL2/SDL.h>
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Updates the keyboard actions.
     */
    auto updateKeyboardActions(SDL_Keycode key) -> void;
}
