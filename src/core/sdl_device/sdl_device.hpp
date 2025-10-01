/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class SDLDevice {
  public:
    SDLDevice() { Initialize(); }

    void ClearCanvas() const;

    void PresentCanvas() const;

    auto GetWindow() const { return m_window; }

    auto GetRenderer() const { return m_renderer; }

  private:
    void Initialize();

    SharedPtr<SDL_Window> m_window;
    SharedPtr<SDL_Renderer> m_renderer;
  };
}
