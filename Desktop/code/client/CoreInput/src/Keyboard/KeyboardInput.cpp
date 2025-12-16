//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "KeyboardInput.hpp"

namespace Forradia {
    void KeyboardInput::Reset() {
        // Clear the pressed keys.
        m_pressed.clear();
    }

    void KeyboardInput::RegisterKeyPress(SDL_Keycode key) {
        // Insert the key into the set of pressed keys.
        m_pressed.insert(key);
    }

    void KeyboardInput::RegisterKeyRelease(SDL_Keycode key) {
        // Remove the key from the set of pressed keys.
        m_pressed.erase(key);
    }

    void KeyboardInput::StartTextInput() {
        // Start text input.
        SDL_StartTextInput();
    }

    void KeyboardInput::StopTextInput() {
        // Stop text input.
        SDL_StopTextInput();

        // Clear the text input.
        m_textInput.clear();
    }

    void KeyboardInput::AddTextInput(StringView text) {
        // Add the text to the text input.
        m_textInput += text;
    }
}