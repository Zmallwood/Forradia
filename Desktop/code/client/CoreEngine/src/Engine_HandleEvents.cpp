//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Engine.hpp"
#include "Keyboard/KeyboardInput.hpp"
#include "Mouse/MouseInput.hpp"

namespace Forradia
{
    void Engine::HandleEvents()
    {
        // To hold polled events.

        SDL_Event event;

        // While there are events to poll.

        while (SDL_PollEvent(&event))
        {
            // Switch on event type.

            switch (event.type)
            {
            case SDL_QUIT:

                // Stop the engine.

                this->Stop();

                break;

            case SDL_KEYDOWN:

                // Register key press.

                _<KeyboardInput>().RegisterKeyPress(event.key.keysym.sym);

                break;

            case SDL_KEYUP:

                // Register key release.

                _<KeyboardInput>().RegisterKeyRelease(event.key.keysym.sym);

                break;

            case SDL_TEXTINPUT:

                // Register text input.

                _<KeyboardInput>().AddTextInput(event.text.text);

                break;

            case SDL_MOUSEBUTTONDOWN:

                // Register mouse button press.

                _<MouseInput>().RegisterMouseButtonDown(event.button.button);

                break;

            case SDL_MOUSEBUTTONUP:

                // Register mouse button release.

                _<MouseInput>().RegisterMouseButtonUp(event.button.button);

                break;

            case SDL_MOUSEWHEEL:

                // Add mouse wheel delta.

                _<MouseInput>().AddMouseWheelDelta(event.wheel.y);

                break;
            }
        }
    }
}