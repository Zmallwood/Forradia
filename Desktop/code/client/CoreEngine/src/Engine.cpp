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
        SDLDevice::Instance().Initialize(gameWindowTitle, clearColor);
        GLDevice::Instance().Initialize();

        // Initialize renderers.
        Color2DRenderer::Instance().Initialize();
        Image2DRenderer::Instance().Initialize();
        GroundRenderer::Instance().Initialize();
        ModelRenderer::Instance().Initialize();
    }

    auto Engine::Run() -> void {
        // Enclose the main game loop in a try-catch block, to catch exceptions thrown anywhere
        // in the game.
        try {
            while (m_running) {
                Cursor::Instance().ResetStyleToNormal();

                this->HandleEvents();

                SceneManager::Instance().UpdateCurrentScene();
                FPSCounter::Instance().Update();

                SDLDevice::Instance().ClearCanvas();
                SceneManager::Instance().RenderCurrentScene();
                Cursor::Instance().Render();
                SDLDevice::Instance().PresentCanvas();
            }
        } catch (std::exception &e) {
            PrintLine("An error occured: " + std::string(e.what()));
        }
    }

    auto Engine::Stop() -> void {
        m_running = false;
    }
}
