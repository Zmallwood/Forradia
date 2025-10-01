/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class sdl_device {
  public:
    sdl_device() { initialize(); }

    void clear_canvas() const;

    void present_canvas() const;

    auto get_window() const { return m_window; }

    auto get_renderer() const { return m_renderer; }

  private:
    void initialize();

    s_ptr<SDL_Window> m_window;
    s_ptr<SDL_Renderer> m_renderer;
  };
}
