/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Coloring/Color.hpp"
#include "Geometry/Size.hpp"

namespace Forradia::Theme0
{
    /**
        Class for storing theme 0 properties.
     */
    class Theme0Properties
    {
      public:
        static Theme0Properties &instance()
        {
            static Theme0Properties instance;
            return instance;
        }

        // Delete copy/move
        Theme0Properties(const Theme0Properties &) = delete;
        Theme0Properties &operator=(const Theme0Properties &) = delete;

        Theme0Properties() = default;

        /**
            Get the game window title.

            @return The game window title.
         */
        static auto getGameWindowTitle() -> std::string;

        /**
            Get the clear color of the canvas.

            @return The clear color of the canvas.
         */
        static auto getClearColor() -> Color;

        /**
            Get the size of the grid rendered by the WorldView.

            @return The size of the grid rendered by the WorldView.
         */
        static auto getGridSize() -> Size;

        /**
            Get the base size of a single world area. This size is being scaled using
            GetWorldScaling() to obtain the resulting world area size.

            @return The base size of a single world area.
         */
        static auto getBaseWorldAreaSize() -> Size;

        /**
            Get the world scaling factor which is applied to the world area size and world
           generation amounts.

            @return The world scaling factor.
         */
        static auto getWorldScaling() -> float;

        /**
            Get the size of a single tile in opengl space.

            @return The size of a single tile in opengl space.
         */
        static auto getTileSize() -> float;

        /**
            Get the height of one unit of elevation in opengl 3D space.

            @return The height of one unit of elevation.
         */
        static auto getElevationHeight() -> float;
    };
}
