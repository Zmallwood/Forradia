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
        SDLDevice();
        
        void ClearCanvas();
        
        void PresentCanvas();

        std::shared_ptr<SDL_Window> m_window;
        std::shared_ptr<SDL_Renderer> m_renderer;
    };
}