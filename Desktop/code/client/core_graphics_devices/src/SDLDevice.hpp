//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// Sets up the objects related to SDL.
    ///
    class SDLDevice
    {
      public:
        ///
        /// Sets up SDL and OpenGL.
        ///
        /// @param gameWindowTitle The title of the game window.
        /// @param clearColor The color to clear the canvas with.
        ///
        void Initialize(StringView gameWindowTitle, Color clearColor);

        ///
        /// Clears the canvas.
        ///
        void ClearCanvas() const;

        ///
        /// Presents the canvas.
        ///
        void PresentCanvas() const;

        ///
        /// Returns the SDL window object.
        ///
        /// @return The SDL window object.
        ///
        auto GetWindow() const
        {
            return m_window;
        }

      private:
        ///
        /// Sets up the SDL window.
        ///
        void SetupSDLWindow();

        ///
        /// Returns the size of the screen.
        ///
        /// @return The size of the screen.
        ///
        Size GetScreenSize() const;

        constexpr static Uint32 k_windowFlags{
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED |
            SDL_WINDOW_FULLSCREEN_DESKTOP |
            SDL_WINDOW_OPENGL}; ///< Flags used in the setup of the SDL window.

        SharedPtr<SDL_Window> m_window; ///< The SDL window.

        String m_gameWindowTitle; ///< The title of the game window.

        Color m_clearColor; ///< The color to clear the canvas with.
    };
}