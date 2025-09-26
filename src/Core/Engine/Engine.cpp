/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Engine.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Core/Cursor/Cursor.hpp"
#include "Core/FPSCounter/FPSCounter.hpp"

namespace Forradia
{
    void Engine::Run()
    {
        Randomize();

        while (m_running)
        {
            PollEvents();

            _<SceneManager>().UpdateCurrentScene();

            _<FPSCounter>().Update();

            _<SDLDevice>().ClearCanvas();

            _<SceneManager>().RenderCurrentScene();

            _<FPSCounter>().Render();

            _<Cursor>().Render();

            _<SDLDevice>().PresentCanvas();
        }
    }

    void Engine::Stop()
    {
        m_running = false;
    }

    void Engine::PollEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:

                m_running = false;

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

                // _<MouseInput>().RegisterMouseButtonDown(
                //     event.button.button
                // );

                break;

            case SDL_MOUSEBUTTONUP:

                // _<MouseInput>().RegisterMouseButtonUp(
                //     event.button.button
                // );

                break;
            }
        }
    }
}
