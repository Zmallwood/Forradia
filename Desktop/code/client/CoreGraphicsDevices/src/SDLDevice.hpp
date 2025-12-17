/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/**
 * Sets up the objects related to SDL.
 */
class SDLDevice {
 public:
  /**
   * Sets up SDL and OpenGL.
   *
   * @param gameWindowTitle The title of the game window.
   * @param clearColor The color to clear the canvas with.
   */
  auto Initialize(StringView gameWindowTitle, Color clearColor) -> void;

  /**
   * Clears the canvas.
   */
  auto ClearCanvas() const -> void;

  /**
   * Presents the canvas.
   */
  auto PresentCanvas() const -> void;

  /**
   * Returns the SDL window object.
   *
   * @return The SDL window object.
   */
  auto GetWindow() const {
    return m_window;
  }

 private:
  auto SetupSDLWindow() -> void;

  auto GetScreenSize() const -> Size;

  constexpr static Uint32 k_windowFlags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                                        SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN_DESKTOP |
                                        SDL_WINDOW_OPENGL};
  SharedPtr<SDL_Window> m_window;
  String m_gameWindowTitle;
  Color m_clearColor;
};
}