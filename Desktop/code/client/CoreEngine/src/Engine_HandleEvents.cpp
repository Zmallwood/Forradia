/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Engine.hpp"
#include "Keyboard/KeyboardInput.hpp"
#include "Mouse/MouseInput.hpp"
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
        _<KeyboardInput>().RegisterKeyPress(event.key.keysym.sym);
        break;
      case SDL_KEYUP:
        _<KeyboardInput>().RegisterKeyRelease(event.key.keysym.sym);
        break;
      case SDL_TEXTINPUT:
        _<KeyboardInput>().AddTextInput(event.text.text);
        break;
      case SDL_MOUSEBUTTONDOWN: {
        _<MouseInput>().RegisterMouseButtonDown(event.button.button);
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          m_ticksLeftMouseButtonFired = GetTicks();
          break;
        case SDL_BUTTON_RIGHT:
          m_ticksRightMouseButtonFired = GetTicks();
          break;
        }
        _<SceneManager>().OnMouseDownCurrentScene(event.button.button);
        break;
      }
      case SDL_MOUSEBUTTONUP: {
        _<MouseInput>().RegisterMouseButtonUp(event.button.button);
        int clickSpeed{0};
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          clickSpeed = GetTicks() - m_ticksLeftMouseButtonFired;
          break;
        case SDL_BUTTON_RIGHT:
          clickSpeed = GetTicks() - m_ticksRightMouseButtonFired;
          break;
        }
        _<SceneManager>().OnMouseUpCurrentScene(event.button.button, clickSpeed);
        break;
      }
      case SDL_MOUSEWHEEL:
        _<MouseInput>().AddMouseWheelDelta(event.wheel.y);
        break;
      }
    }
  }
}
