/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "SDLDevice.hpp"

namespace Forradia {
void SDLDevice::SetupSDLWindow() {
  auto screenSize{this->GetScreenSize()};
  m_window = SharedPtr<SDL_Window>(
      SDL_CreateWindow(m_gameWindowTitle.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       screenSize.width, screenSize.height, k_windowFlags),
      SDLDeleter());
  if (nullptr == m_window)
    PrintLine("Window could not be created. "
              "SDL Error: " +
              String(SDL_GetError()));
}
}