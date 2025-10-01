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
  void engine::Run() {
    Randomize();
    GetSingleton<sdl_device>();
    while (m_running) {
      GetSingleton<keyboard_input>().Reset();
      GetSingleton<mouse_input>().Reset();
      GetSingleton<cursor>().ResetStyleToDefault();
      PollEvents();
      GetSingleton<scene_manager>().UpdateCurrentScene();
      GetSingleton<fps_counter>().Update();
      GetSingleton<sdl_device>().ClearCanvas();
      GetSingleton<scene_manager>().RenderCurrentScene();
      GetSingleton<cursor>().Render();
      GetSingleton<sdl_device>().PresentCanvas();
    }
  }

  void engine::Stop() { m_running = false; }
}
