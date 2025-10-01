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
  void Engine::Run() {
    Randomize();
    GetSingleton<SDLDevice>();
    while (m_running) {
      GetSingleton<KeyboardInput>().Reset();
      GetSingleton<MouseInput>().Reset();
      GetSingleton<Cursor>().ResetStyleToDefault();
      PollEvents();
      GetSingleton<SceneManager>().UpdateCurrentScene();
      GetSingleton<FPSCounter>().Update();
      GetSingleton<SDLDevice>().ClearCanvas();
      GetSingleton<SceneManager>().RenderCurrentScene();
      GetSingleton<Cursor>().Render();
      GetSingleton<SDLDevice>().PresentCanvas();
    }
  }

  void Engine::Stop() { m_running = false; }
}
