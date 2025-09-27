/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "PollEvents.hpp"
#include "Core/Engine/Engine.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"

 namespace Forradia
 {
    void PollEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:

                _<Engine>().Stop();

                break;

            case SDL_KEYDOWN:

                _<KeyboardInput>().RegisterKeyPress(
                    event.key.keysym.sym);

                break;

            case SDL_KEYUP:

                _<KeyboardInput>().RegisterKeyRelease(
                    event.key.keysym.sym);

                break;

            case SDL_MOUSEBUTTONDOWN:

                _<MouseInput>().RegisterMouseButtonDown(
                    event.button.button
                );

                break;

            case SDL_MOUSEBUTTONUP:

                _<MouseInput>().RegisterMouseButtonUp(
                    event.button.button
                );

                break;
            }
        }
    }
 }