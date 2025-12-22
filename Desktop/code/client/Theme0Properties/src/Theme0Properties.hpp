/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Geometry/Size.hpp"

namespace Forradia::Theme0 {
    /**
     * Class for storing theme 0 properties.
     */
    class Theme0Properties {
      public:
        static Theme0Properties &Instance() {
            static Theme0Properties instance;
            return instance;
        }

        // Delete copy/move
        Theme0Properties(const Theme0Properties &) = delete;
        Theme0Properties &operator=(const Theme0Properties &) = delete;

        Theme0Properties() = default;

        /**
         * Get the game window title.
         *
         * @return The game window title.
         */
        auto GetGameWindowTitle() const -> std::string;

        /**
         * Get the clear color of the canvas.
         *
         * @return The clear color of the canvas.
         */
        auto GetClearColor() const -> Color;

        /**
         * Get the size of the grid rendered by the WorldView.
         *
         * @return The size of the grid rendered by the WorldView.
         */
        auto GetGridSize() const -> Size;

        /**
         * Get the base size of a single world area. This size is being scaled using
         * GetWorldScaling() to obtain the resulting world area size.
         *
         * @return The base size of a single world area.
         */
        auto GetBaseWorldAreaSize() const -> Size;

        /**
         * Get the world scaling factor which is applied to the world area size and world generation
         * amounts.
         *
         * @return The world scaling factor.
         */
        auto GetWorldScaling() const -> float;

        /**
         * Get the size of a single tile in opengl space.
         *
         * @return The size of a single tile in opengl space.
         */
        auto GetTileSize() const -> float;

        /**
         * Get the height of one unit of elevation in opengl 3D space.
         *
         * @return The height of one unit of elevation.
         */
        auto GetElevationHeight() const -> float;
    };
}
