/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "poll_events.hpp"
#include "core/engine/engine.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "core/input/mouse/mouse_input.hpp"

namespace Forradia {
  void PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        GetSingleton<Engine>().Stop();
        break;
      case SDL_KEYDOWN:
        GetSingleton<KeyboardInput>().RegisterKeyPress(event.key.keysym.sym);
        break;
      case SDL_KEYUP:
        GetSingleton<KeyboardInput>().RegisterKeyRelease(event.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        GetSingleton<MouseInput>().RegisterMouseButtonDown(event.button.button);
        break;
      case SDL_MOUSEBUTTONUP:
        GetSingleton<MouseInput>().RegisterMouseButtonUp(event.button.button);
        break;
      }
    }
  }
}