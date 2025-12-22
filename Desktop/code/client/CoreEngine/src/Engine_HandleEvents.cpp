/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Engine.hpp"
#include "SceneManager.hpp"
#include "Singleton.hpp"
#include "TimeUtilities.hpp"
#include <SDL2/SDL.h>

namespace Forradia {
    auto Engine::HandleEvents() -> void {
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_QUIT:
                this->Stop();
                break;
            case SDL_KEYDOWN:
                SceneManager::Instance().OnKeyDownCurrentScene(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                SceneManager::Instance().OnKeyUpCurrentScene(event.key.keysym.sym);
                break;
            case SDL_TEXTINPUT:
                SceneManager::Instance().OnTextInputCurrentScene(event.text.text);
                break;
            case SDL_MOUSEBUTTONDOWN: {
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    m_ticksLeftMouseButtonFired = GetTicks();
                    break;
                case SDL_BUTTON_RIGHT:
                    m_ticksRightMouseButtonFired = GetTicks();
                    break;
                }
                SceneManager::Instance().OnMouseDownCurrentScene(event.button.button);
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                int clickSpeed{0};
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    clickSpeed = GetTicks() - m_ticksLeftMouseButtonFired;
                    break;
                case SDL_BUTTON_RIGHT:
                    clickSpeed = GetTicks() - m_ticksRightMouseButtonFired;
                    break;
                }
                SceneManager::Instance().OnMouseUpCurrentScene(event.button.button, clickSpeed);
                break;
            }
            case SDL_MOUSEWHEEL:
                SceneManager::Instance().OnMouseWheelCurrentScene(event.wheel.y);
                break;
            }
        }
    }
}
