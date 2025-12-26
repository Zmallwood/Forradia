/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Matter/Coloring/Color.hpp"
    #include "ForradiaEngine/Common/Matter/Geometry.hpp"
    #include <SDL2/SDL.h>
    #include <memory>
    #include <string>
// clang-format on

struct SDL_Window;

using Uint32 = uint32_t;

namespace ForradiaEngine
{
    /**
     *  Sets up the objects related to SDL.
     */
    class SDLDevice
    {
      public:
        static auto instance() -> SDLDevice &
        {
            static SDLDevice instance;
            return instance;
        }

        SDLDevice(const SDLDevice &) = delete;

        auto operator=(const SDLDevice &) -> SDLDevice & = delete;

        SDLDevice() = default;

        /**
         *  Sets up SDL and OpenGL.
         *
         *  @param gameWindowTitle The title of the game window.
         *  @param clearColor The color to clear the canvas with.
         */
        auto initialize(std::string_view gameWindowTitle, Color clearColor) -> void;

        /**
         *  Clears the canvas.
         */
        auto clearCanvas() const -> void;

        /**
         *  Presents the canvas.
         */
        auto presentCanvas() const -> void;

        /**
         *  Returns the SDL window object.
         *
         *  @return The SDL window object.
         */
        [[nodiscard]] auto getWindow() const -> std::shared_ptr<SDL_Window>
        {
            return m_window;
        }

      private:
        auto setupSDLWindow() -> void;

        [[nodiscard]] static auto getScreenSize() -> Size;

        constexpr static Uint32 k_windowFlags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN_DESKTOP |
                                              SDL_WINDOW_OPENGL};
        std::shared_ptr<SDL_Window> m_window{};
        std::string m_gameWindowTitle{};
        Color m_clearColor{};
    };
}
