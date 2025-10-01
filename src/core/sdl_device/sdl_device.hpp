/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class sdl_device {
  public:
    sdl_device() { Initialize(); }

    void ClearCanvas() const;

    void PresentCanvas() const;

    auto GetWindow() const { return m_window; }

    auto GetRenderer() const { return m_renderer; }

  private:
    void Initialize();

    s_ptr<SDL_Window> m_window;
    s_ptr<SDL_Renderer> m_renderer;
  };
}
