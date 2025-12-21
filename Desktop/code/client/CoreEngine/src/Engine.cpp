/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Engine.hpp"
#include "Color2DRenderer.hpp"
#include "Cursor.hpp"
#include "FPSCounter.hpp"
#include "GLDevice.hpp"
#include "GroundRenderer.hpp"
#include "Image2DRenderer.hpp"
#include "MessageUtilities.hpp"
#include "ModelRenderer.hpp"
#include "RandomizationUtilities.hpp"
#include "SDLDevice.hpp"
#include "SceneManager.hpp"
#include "Singleton.hpp"

namespace Forradia {
    auto Engine::Initialize(std::string_view gameWindowTitle, Color clearColor) -> void {
        // Initialize random number generator so that unique random numbers are generated on
        // each game run.
        Randomize();

        // Initialize graphics devices.
        Singleton<SDLDevice>().Initialize(gameWindowTitle, clearColor);
        Singleton<GLDevice>().Initialize();

        // Initialize renderers.
        Singleton<Color2DRenderer>().Initialize();
        Singleton<Image2DRenderer>().Initialize();
        Singleton<GroundRenderer>().Initialize();
        Singleton<ModelRenderer>().Initialize();
    }

    auto Engine::Run() -> void {
        // Enclose the main game loop in a try-catch block, to catch exceptions thrown anywhere
        // in the game.
        try {
            while (m_running) {
                Singleton<Cursor>().ResetStyleToNormal();

                this->HandleEvents();

                Singleton<SceneManager>().UpdateCurrentScene();
                Singleton<FPSCounter>().Update();

                Singleton<SDLDevice>().ClearCanvas();
                Singleton<SceneManager>().RenderCurrentScene();
                Singleton<Cursor>().Render();
                Singleton<SDLDevice>().PresentCanvas();
            }
        } catch (std::exception &e) {
            PrintLine("An error occured: " + std::string(e.what()));
        }
    }

    auto Engine::Stop() -> void {
        m_running = false;
    }
}
