/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "sdl_device.hpp"
#include "sub/create_renderer.hpp"
#include "sub/create_window.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"

namespace forr {
  void sdl_device::initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);
    m_window = create_window();
    if (m_window) {
      m_renderer = create_renderer(m_window);
    }
  }

  void sdl_device::clear_canvas() const {
    SDL_Color clearColor{
        get_singleton<game_properties>().k_clearColor.to_sdl_color()};
    SDL_SetRenderDrawColor(m_renderer.get(), clearColor.r, clearColor.g,
                           clearColor.b, 255);
    SDL_RenderClear(m_renderer.get());
  }

  void sdl_device::present_canvas() const {
    SDL_RenderPresent(m_renderer.get());
  }
}
