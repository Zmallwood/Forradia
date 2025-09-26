/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class KeyboardInput
    {
    public:
        void Reset();

        void RegisterKeyPress(SDL_Keycode key);

        void RegisterKeyRelease(SDL_Keycode key);

        bool KeyIsPressed(SDL_Keycode key) const;

        bool KeyIsPressedPickResult(SDL_Keycode key);

        bool AnyKeyIsPressedPickResult();

    private:
        std::set<SDL_Keycode> m_pressedKeys;
    };
}
