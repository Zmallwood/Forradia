/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Engine.hpp"
#include "core/cursor/Cursor.hpp"
#include "core/fps_counter/FPSCounter.hpp"
#include "core/input/keyboard/KeyboardInput.hpp"
#include "core/input/mouse/MouseInput.hpp"
#include "core/scenes_core/SceneManager.hpp"
#include "core/sdl_device/SDLDevice.hpp"
#include "sub/PollEvents.hpp"

namespace Forradia {
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
