/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Engine.hpp"
#include "Keyboard/KeyboardInput.hpp"
#include "Mouse/MouseInput.hpp"

namespace Forradia {
auto Engine::HandleEvents() -> void {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
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
    case SDL_MOUSEBUTTONDOWN:
      _<MouseInput>().RegisterMouseButtonDown(event.button.button);
      break;
    case SDL_MOUSEBUTTONUP:
      _<MouseInput>().RegisterMouseButtonUp(event.button.button);
      break;
    case SDL_MOUSEWHEEL:
      _<MouseInput>().AddMouseWheelDelta(event.wheel.y);
      break;
    }
  }
}
}
