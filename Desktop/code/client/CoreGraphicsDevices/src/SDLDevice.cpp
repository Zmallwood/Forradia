/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "SDLDevice.hpp"

namespace Forradia {
  auto SDLDevice::Initialize(StringView gameWindowTitle, Color clearColor) -> void {
    m_gameWindowTitle = gameWindowTitle;
    m_clearColor = clearColor;
    SDL_Init(SDL_INIT_EVERYTHING);
    this->SetupSDLWindow();
  }

  auto SDLDevice::ClearCanvas() const -> void {
    auto clearColor{m_clearColor};
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  auto SDLDevice::PresentCanvas() const -> void {
    SDL_GL_SwapWindow(m_window.get());
  }

  auto SDLDevice::GetScreenSize() const -> Size {
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    auto width{displayMode.w};
    auto height{displayMode.h};
    return {width, height};
  }
}
