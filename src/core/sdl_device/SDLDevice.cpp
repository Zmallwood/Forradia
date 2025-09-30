/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "SDLDevice.hpp"
#include "sub/CreateRenderer.hpp"
#include "sub/CreateWindow.hpp"
#include "theme_0/theme_0_mechanics/configuration/GameProperties.hpp"

namespace Forradia {
  void SDLDevice::Initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);

    m_window = CreateWindow();

    if (m_window) {
      m_renderer = CreateRenderer(m_window);
    }
  }

  void SDLDevice::ClearCanvas() const {
    SDL_Color clearColor{GetSingleton<GameProperties>().k_clearColor.ToSDLColor()};

    SDL_SetRenderDrawColor(m_renderer.get(), clearColor.r, clearColor.g,
                           clearColor.b, 255);

    SDL_RenderClear(m_renderer.get());
  }

  void SDLDevice::PresentCanvas() const { SDL_RenderPresent(m_renderer.get()); }
}
