//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Engine.hpp"

#include "GLDevice.hpp"

#include "MinorComponents/Cursor.hpp"

#include "MinorComponents/FPSCounter.hpp"

#include "SDLDevice.hpp"

#include "ScenesCore/SceneManager.hpp"

#include "Input/Keyboard/KeyboardInput.hpp"

#include "Input/Mouse/MouseInput.hpp"

namespace Forradia
{
    void Engine::Initialize(StringView gameWindowTitle,
                            Color clearColor) const
    {
        Randomize();

        _<SDLDevice>().Initialize(gameWindowTitle,
                                  clearColor);

        _<GLDevice>().Initialize();
    }

    void Engine::Run()
    {
        try
        {
            while (m_running)
            {
                _<MouseInput>().Reset();

                _<Cursor>().ResetStyleToNormal();

                this->PollEvents();

                _<SceneManager>().UpdateCurrentScene();

                _<FPSCounter>().Update();

                _<SDLDevice>().ClearCanvas();

                _<SceneManager>().RenderCurrentScene();

                _<Cursor>().Render();

                _<SDLDevice>().PresentCanvas();
            }
        }
        catch (std::exception &e)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                     "Error", e.what(),
                                     nullptr);
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

                this->Stop();

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

                _<MouseInput>()
                    .RegisterMouseButtonDown(
                        event.button.button);

                break;

            case SDL_MOUSEBUTTONUP:

                _<MouseInput>()
                    .RegisterMouseButtonUp(
                        event.button.button);

                break;
            }
        }
    }
}