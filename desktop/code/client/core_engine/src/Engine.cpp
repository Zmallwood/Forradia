//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Engine.hpp"

#include "GLDevice.hpp"

#include "Cursor.hpp"

#include "FPSCounter.hpp"

#include "SDLDevice.hpp"

#include "SceneManager.hpp"

#include "Mouse/MouseInput.hpp"

#include "Color2DRenderer.hpp"

#include "Image2DRenderer.hpp"

#include "GroundRenderer.hpp"

#include "ModelRenderer.hpp"

namespace Forradia
{
    void Engine::Initialize(StringView gameWindowTitle,
                            Color clearColor) const
    {
        // Initialize random number generator so that unique
        // random numbers are generated on each game run.

        Randomize();

        // Initialize SDL and GL devices.

        _<SDLDevice>().Initialize(gameWindowTitle,
                                  clearColor);

        _<GLDevice>().Initialize();

        // Initialize renderers.

        _<Color2DRenderer>().Initialize();

        _<Image2DRenderer>().Initialize();

        _<GroundRenderer>().Initialize();

        _<ModelRenderer>().Initialize();
    }

    void Engine::Run()
    {
        // Enclose the main game loop in a try-catch block,
        // to catch exceptions thrown anywhere in the game.

        try
        {
            // Main game loop.

            while (m_running)
            {
                // Reset the mouse input and cursor before
                // polling events.

                _<MouseInput>().Reset();

                _<Cursor>().ResetStyleToNormal();

                // Poll events and handle them.

                this->HandleEvents();

                // Update.

                _<SceneManager>().UpdateCurrentScene();

                _<FPSCounter>().Update();

                // Render.

                _<SDLDevice>().ClearCanvas();

                _<SceneManager>().RenderCurrentScene();

                _<Cursor>().Render();

                // Present the canvas.

                _<SDLDevice>().PresentCanvas();
            }
        }
        catch (std::exception &e)
        {
            // Print error message on catched exception.

            PrintLine("An error occured: " +
                      String(e.what()));
        }
    }

    void Engine::Stop()
    {
        // Stop the engine.

        m_running = false;
    }
}