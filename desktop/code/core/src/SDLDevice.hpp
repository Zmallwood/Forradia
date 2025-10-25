//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class SDLDevice
    {
      public:
        ~SDLDevice();

        void Initialize(StringView gameWindowTitle,
                        Color clearColor);

        void ClearCanvas() const;

        void PresentCanvas() const;

        auto GetWindow() const
        {
            return m_window;
        }

      private:
        void SetupSDLWindow();

        void SetupGL();

        Size GetScreenSize() const;

        SharedPtr<SDL_Window> m_window;

        SharedPtr<SDL_GLContext> m_context;

        String m_gameWindowTitle;

        Color m_clearColor;
    };
}