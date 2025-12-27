/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Engine.hpp"

#include "ForradiaEngine/GraphicsDevices/GLDevice.hpp"
#include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
#include "ForradiaEngine/MinorComponents/Cursor.hpp"
#include "ForradiaEngine/MinorComponents/FPSCounter.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Rendering/Colors/Color2DRenderer.hpp"
#include "ForradiaEngine/Rendering/Ground/GroundRenderer.hpp"
#include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
#include "ForradiaEngine/Rendering/Models/ModelRenderer.hpp"
#include "ForradiaEngine/ScenesCore.hpp"

namespace ForradiaEngine
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

    auto Engine::handleEvents() -> void
    {
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0)
        {
            this->handleSingleEvent(event);
        }
    }

    auto Engine::handleSingleEvent(SDL_Event &event) -> void
    {
        switch (event.type)
        {
        case SDL_QUIT:
            this->stop();
            break;

        case SDL_KEYDOWN:
            SceneManager::instance().onKeyDownCurrentScene(event.key.keysym.sym);
            break;

        case SDL_KEYUP:
            SceneManager::instance().onKeyUpCurrentScene(event.key.keysym.sym);
            break;

        case SDL_TEXTINPUT:
            SceneManager::instance().onTextInputCurrentScene(event.text.text);
            break;

        case SDL_MOUSEBUTTONDOWN:
        {
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                m_ticksLeftMouseButtonFired = getTicks();
                break;
            case SDL_BUTTON_RIGHT:
                m_ticksRightMouseButtonFired = getTicks();
                break;
            default:
                break;
            }
            SceneManager::instance().onMouseDownCurrentScene(event.button.button);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            int clickSpeed{0};
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                clickSpeed = getTicks() - m_ticksLeftMouseButtonFired;
                break;
            case SDL_BUTTON_RIGHT:
                clickSpeed = getTicks() - m_ticksRightMouseButtonFired;
                break;
            default:
                break;
            }
            SceneManager::instance().onMouseUpCurrentScene(event.button.button, clickSpeed);
            break;
        }
        case SDL_MOUSEWHEEL:
            SceneManager::instance().onMouseWheelCurrentScene(event.wheel.y);

        default:
            break;
        }
    }
}
