/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Engine.hpp"
#include "ScenesCore/SceneManager.hpp"
#include "Common/Utilities/TimeUtilities.hpp"
#include <SDL2/SDL.h>

namespace Forradia
{
    auto Engine::handleEvents() -> void
    {
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0)
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
                break;
            default:
                break;
            }
        }
    }
}
