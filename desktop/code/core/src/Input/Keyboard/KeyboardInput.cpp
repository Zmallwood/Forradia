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
        m_pressed.clear();
    }

    void KeyboardInput::RegisterKeyPress(SDL_Keycode key)
    {
        m_pressed.insert(key);
    }

    void KeyboardInput::RegisterKeyRelease(SDL_Keycode key)
    {
        m_pressed.erase(key);
    }

    bool KeyboardInput::KeyIsPressed(SDL_Keycode key) const
    {
        return m_pressed.contains(key);
    }

    bool
    KeyboardInput::KeyIsPressedPickResult(SDL_Keycode key)
    {
        auto result{m_pressed.contains(key)};

        m_pressed.erase(key);

        return result;
    }

    bool KeyboardInput::AnyKeyIsPressedPickResult()
    {
        auto result{m_pressed.size() > 0};

        m_pressed.clear();

        return result;
    }
}