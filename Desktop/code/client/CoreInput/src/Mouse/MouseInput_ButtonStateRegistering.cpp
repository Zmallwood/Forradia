//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "MouseInput.hpp"

namespace Forradia {
    void MouseInput::RegisterMouseButtonDown(Uint8 button) {
        // Determine which button has been pressed.
        switch (button) {
        case SDL_BUTTON_LEFT:
            // Register that the left mouse button has been pressed.
            m_leftMouseButton.RegisterPress();

            break;

        case SDL_BUTTON_RIGHT:
            // Register that the right mouse button has been pressed.
            m_rightMouseButton.RegisterPress();

            break;
        }
    }

    void MouseInput::RegisterMouseButtonUp(Uint8 button) {
        // Determine which button has been released.
        switch (button) {
        case SDL_BUTTON_LEFT:
            // Register that the left mouse button has been released.
            m_leftMouseButton.RegisterRelease();

            break;

        case SDL_BUTTON_RIGHT:
            // Register that the right mouse button has been released.
            m_rightMouseButton.RegisterRelease();

            break;
        }
    }
}