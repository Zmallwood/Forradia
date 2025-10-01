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
#include "sub/poll_events.hpp"

namespace forr {
  void engine::run() {
    Randomize();
    GetSingleton<sdl_device>();
    while (m_running) {
      GetSingleton<keyboard_input>().reset();
      GetSingleton<mouse_input>().reset();
      GetSingleton<cursor>().reset_style_to_default();
      PollEvents();
      GetSingleton<scene_manager>().update_current_scene();
      GetSingleton<fps_counter>().update();
      GetSingleton<sdl_device>().clear_canvas();
      GetSingleton<scene_manager>().render_current_scene();
      GetSingleton<cursor>().render();
      GetSingleton<sdl_device>().present_canvas();
    }
  }

  void engine::stop() { m_running = false; }
}
