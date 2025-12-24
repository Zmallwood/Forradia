/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Engine.hpp"
#include "GraphicsDevices/GLDevice.hpp"
#include "GraphicsDevices/SDLDevice.hpp"
#include "MessageUtilities.hpp"
#include "MinorComponents/Cursor.hpp"
#include "MinorComponents/FPSCounter.hpp"
#include "RandomizationUtilities.hpp"
#include "Rendering/Colors/Color2DRenderer.hpp"
#include "Rendering/Ground/GroundRenderer.hpp"
#include "Rendering/Images/Image2DRenderer.hpp"
#include "Rendering/Models/ModelRenderer.hpp"
#include "ScenesCore/SceneManager.hpp"

namespace Forradia
{
    auto Engine::initialize(std::string_view gameWindowTitle, Color clearColor) -> void
    {
        // Initialize random number generator so that unique random numbers are generated on
        // each game run.
        randomize();

        // Initialize graphics devices.
        SDLDevice::instance().initialize(gameWindowTitle, clearColor);
        GLDevice::instance().initialize();

        // Initialize renderers.
        Color2DRenderer::instance().initialize();
        Image2DRenderer::instance().initialize();
        GroundRenderer::instance().initialize();
        ModelRenderer::instance().initialize();
    }

    auto Engine::run() -> void
    {
        // Enclose the main game loop in a try-catch block, to catch exceptions thrown anywhere
        // in the game.
        try
        {
            while (m_running)
            {
                Cursor::instance().resetStyleToNormal();

                this->handleEvents();

                SceneManager::instance().updateCurrentScene();
                FPSCounter::instance().update();

                SDLDevice::instance().clearCanvas();
                SceneManager::instance().renderCurrentScene();
                Cursor::instance().render();
                SDLDevice::instance().presentCanvas();
            }
        }
        catch (std::exception &e)
        {
            printLine("Caught exception: " + std::string(e.what()));
        }
    }

    auto Engine::stop() -> void
    {
        m_running = false;
    }
}
