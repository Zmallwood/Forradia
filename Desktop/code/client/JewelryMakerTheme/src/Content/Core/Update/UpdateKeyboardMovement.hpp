/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <SDL2/SDL.h>
// clang-format on

namespace Forradia::Theme0
{
    /**
     *  Updates the keyboard movement.
     */
    auto updateKeyboardMovementStart(SDL_Keycode key) -> void;

    auto updateKeyboardMovementStop() -> void;
}
