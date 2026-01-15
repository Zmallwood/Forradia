/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <SDL2/SDL.h>

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Starts the keyboard movement of the player.
     *
     *  @param key The key that was pressed.
     */
    auto updateKeyboardMovementStart(SDL_Keycode key) -> void;

    /**
     *  Stops the keyboard movement of the player.
     */
    auto updateKeyboardMovementStop() -> void;
}
