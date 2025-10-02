/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "engine.hpp"
#include "core/cursor/cursor.hpp"
#include "core/fps_counter/fps_counter.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/scenes_core/scene_manager.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  void engine::run() {
    randomize();
    get_singleton<sdl_device>();
    while (m_running) {
      get_singleton<keyboard_input>().reset();
      get_singleton<mouse_input>().reset();
      get_singleton<cursor>().reset_style_to_default();
      poll_events();
      get_singleton<scene_manager>().update_current_scene();
      get_singleton<fps_counter>().update();
      get_singleton<sdl_device>().clear_canvas();
      get_singleton<scene_manager>().render_current_scene();
      get_singleton<cursor>().render();
      get_singleton<sdl_device>().present_canvas();
    }
  }

  void engine::stop() { m_running = false; }

  void engine::poll_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        m_running = false;
        break;
      case SDL_KEYDOWN:
        get_singleton<keyboard_input>().register_key_press(
            event.key.keysym.sym);
        break;
      case SDL_KEYUP:
        get_singleton<keyboard_input>().register_key_release(
            event.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        get_singleton<mouse_input>().register_mouse_button_down(
            event.button.button);
        break;
      case SDL_MOUSEBUTTONUP:
        get_singleton<mouse_input>().register_mouse_button_up(
            event.button.button);
        break;
      }
    }
  }
}
