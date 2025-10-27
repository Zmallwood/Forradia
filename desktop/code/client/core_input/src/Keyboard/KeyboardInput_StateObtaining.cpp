//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "KeyboardInput.hpp"

namespace Forradia
{

    bool KeyboardInput::KeyIsPressed(SDL_Keycode key) const
    {
        // Check if the key is in the set of pressed keys.

        return m_pressed.contains(key);
    }

    bool
    KeyboardInput::KeyIsPressedPickResult(SDL_Keycode key)
    {
        // Check if the key is in the set of pressed keys
        // and store as result.

        auto result{m_pressed.contains(key)};

        // Remove the key from the set of pressed keys.

        m_pressed.erase(key);

        // Return the result.

        return result;
    }

    bool KeyboardInput::AnyKeyIsPressedPickResult()
    {
        // Check if any key is in the set of pressed keys
        // and store as result.

        auto result{m_pressed.size() > 0};

        // Clear the set of pressed keys.

        m_pressed.clear();

        // Return the result.

        return result;
    }
}