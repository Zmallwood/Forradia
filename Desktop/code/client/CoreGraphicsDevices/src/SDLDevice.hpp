/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Coloring/Color.hpp"
#include "Geometry/Size.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <string>

struct SDL_Window;
using Uint32 = uint32_t;

namespace Forradia
{
    /**
     * Sets up the objects related to SDL.
     */
    class SDLDevice
    {
      public:
        static auto Instance() -> SDLDevice &
        {
            static SDLDevice instance;
            return instance;
        }

        // Delete copy/move
        SDLDevice(const SDLDevice &) = delete;

        auto operator=(const SDLDevice &) -> SDLDevice & = delete;

        SDLDevice() = default;

        /**
         * Sets up SDL and OpenGL.
         *
         * @param gameWindowTitle The title of the game window.
         * @param clearColor The color to clear the canvas with.
         */
        auto Initialize(std::string_view gameWindowTitle, Color clearColor) -> void;

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
        [[nodiscard]] auto GetWindow() const -> std::shared_ptr<SDL_Window>
        {
            return m_window;
        }

      private:
        auto SetupSDLWindow() -> void;

        [[nodiscard]] static auto GetScreenSize() -> Size;

        constexpr static Uint32 k_windowFlags{SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                                              SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN_DESKTOP |
                                              SDL_WINDOW_OPENGL};
        std::shared_ptr<SDL_Window> m_window{};
        std::string m_gameWindowTitle{};
        Color m_clearColor{};
    };
}
