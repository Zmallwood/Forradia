/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Engine.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"
#include "Core/ScenesCore/SceneManager.hpp"
#include "Core/Cursor/Cursor.hpp"
#include "Core/FPSCounter/FPSCounter.hpp"
#include "Sub/PollEvents.hpp"

namespace Forradia
{
    void Engine::Run()
    {
        Randomize();

        _<SDLDevice>();

        while (m_running)
        {
            _<Cursor>().ResetStyleToDefault();

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
}
