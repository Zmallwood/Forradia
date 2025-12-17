/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Engine.hpp"
#include "Color2DRenderer.hpp"
#include "Cursor.hpp"
#include "FPSCounter.hpp"
#include "GLDevice.hpp"
#include "GroundRenderer.hpp"
#include "Image2DRenderer.hpp"
#include "ModelRenderer.hpp"
#include "Mouse/MouseInput.hpp"
#include "SDLDevice.hpp"
#include "SceneManager.hpp"

namespace Forradia {
auto Engine::Initialize(StringView gameWindowTitle, Color clearColor) const -> void {
  // Initialize random number generator so that unique random numbers are generated on
  // each game run.
  Randomize();

  // Initialize graphics devices.
  _<SDLDevice>().Initialize(gameWindowTitle, clearColor);
  _<GLDevice>().Initialize();

  // Initialize renderers.
  _<Color2DRenderer>().Initialize();
  _<Image2DRenderer>().Initialize();
  _<GroundRenderer>().Initialize();
  _<ModelRenderer>().Initialize();
}

auto Engine::Run() -> void {
  // Enclose the main game loop in a try-catch block, to catch exceptions thrown anywhere
  // in the game.
  try {
    while (m_running) {
      _<MouseInput>().Reset();
      _<Cursor>().ResetStyleToNormal();

      this->HandleEvents();

      _<SceneManager>().UpdateCurrentScene();
      _<FPSCounter>().Update();

      _<SDLDevice>().ClearCanvas();
      _<SceneManager>().RenderCurrentScene();
      _<Cursor>().Render();
      _<SDLDevice>().PresentCanvas();
    }
  } catch (std::exception &e) {
    PrintLine("An error occured: " + String(e.what()));
  }
}

auto Engine::Stop() -> void {
  m_running = false;
}
}
