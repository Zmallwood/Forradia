/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "poll_events.hpp"
#include "core/engine/engine.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "core/input/mouse/mouse_input.hpp"

namespace forr {
  void PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        GetSingleton<engine>().stop();
        break;
      case SDL_KEYDOWN:
        GetSingleton<keyboard_input>().register_key_press(event.key.keysym.sym);
        break;
      case SDL_KEYUP:
        GetSingleton<keyboard_input>().register_key_release(
            event.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        GetSingleton<mouse_input>().register_mouse_button_down(
            event.button.button);
        break;
      case SDL_MOUSEBUTTONUP:
        GetSingleton<mouse_input>().register_mouse_button_up(
            event.button.button);
        break;
      }
    }
  }
}