//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "KeyboardInput.hpp"

namespace Forradia
{
    void KeyboardInput::Reset()
    {
        // Clear the pressed keys.

        m_pressed.clear();
    }

    void KeyboardInput::RegisterKeyPress(SDL_Keycode key)
    {
        // Insert the key into the set of pressed keys.

        m_pressed.insert(key);
    }

    void KeyboardInput::RegisterKeyRelease(SDL_Keycode key)
    {
        // Remove the key from the set of pressed keys.

        m_pressed.erase(key);
    }
}